using System.IO.Compression;
using System.Net.Http.Json;
using System.Text.RegularExpressions;
using Archiver;
using AssetRipper.VersionUtilities;
using LibGit2Sharp;

const string baseUrl = "https://unity.bepinex.dev/libil2cpp-source";

using var httpClient = new HttpClient();
httpClient.DefaultRequestHeaders.Add("Accept", "application/json");

var files = await httpClient.GetFromJsonAsync<CaddyIndexFile[]>(baseUrl) ?? throw new Exception("Failed to download file index");

var zipsPath = Path.Combine(Directory.GetCurrentDirectory(), "zips");
Directory.CreateDirectory(zipsPath);

var contexts = files
    .Where(f => f.Name.EndsWith(".zip"))
    .Select(f =>
        new
        {
            Name = Path.GetFileNameWithoutExtension(f.Name),
            Version = UnityVersion.Parse(Path.GetFileNameWithoutExtension(f.Name)),
            DownloadUrl = Path.Combine(baseUrl, f.Url),
            ZipPath = Path.Join(zipsPath, f.Name),
        })
    .OrderBy(c => c.Version)
    .ToArray();

await Parallel.ForEachAsync(contexts.Where(c => !File.Exists(c.ZipPath)), async (file, token) =>
{
    Console.WriteLine("Downloading " + file.DownloadUrl);
    var response = await httpClient.GetAsync(file.DownloadUrl, token);

    await using (var stream = await response.Content.ReadAsStreamAsync(token))
    await using (var fileStream = File.OpenWrite(file.ZipPath))
    {
        await stream.CopyToAsync(fileStream, token);
    }
});

var repoPath = Path.Combine(Directory.GetCurrentDirectory(), "archive");
if (Directory.Exists(repoPath)) Directory.Delete(repoPath, true);
Directory.CreateDirectory(repoPath);

Repository.Init(repoPath);
using (var repository = new Repository(repoPath))
{
    foreach (var tag in repository.Tags) repository.Tags.Remove(tag);
    repository.Branches.Remove("archive");
    repository.Refs.UpdateTarget("HEAD", "refs/heads/archive");

    foreach (var context in contexts)
    {
        foreach (var file in Directory.GetFiles(repoPath)) File.Delete(file);
        foreach (var directory in Directory.GetDirectories(repoPath))
        {
            if (Path.GetFileName(directory) == ".git") continue;
            Directory.Delete(directory, true);
        }

        DateTimeOffset lastWriteTime;

        using (var archive = ZipFile.Open(context.ZipPath, ZipArchiveMode.Read))
        {
            lastWriteTime = archive.Entries.Max(x => x.LastWriteTime);
            Console.WriteLine($"Extracting {context.Name} ({lastWriteTime})");
            archive.ExtractToDirectory(repoPath);
        }

        var message = context.Name;

        if (context.Version.IsGreater(5, 2, 1))
        {
            var path = Path.Combine(repoPath, "vm", context.Version.IsGreaterEqual(2020, 2, 0) ? "GlobalMetadata.cpp" : "MetadataCache.cpp");
            var match = MetadataVersionRegex().Match(await File.ReadAllTextAsync(path));
            var metadataVersion = int.Parse(match.Groups["version"].Value);

            message += $" (v{metadataVersion})";
        }

        Commands.Stage(repository, "*");

        var signature = new Signature("github-actions[bot]", "github-actions[bot]@users.noreply.github.com", lastWriteTime);

        Commit commit;

        if (repository.RetrieveStatus().IsDirty)
        {
            commit = repository.Commit(message, signature, signature);
        }
        else
        {
            commit = repository.Head.Tip;
        }

        repository.Tags.Add(context.Name, commit, signature, context.Name);
    }
}

internal partial class Program
{
    [GeneratedRegex("\\(s_GlobalMetadataHeader->version == (?<version>\\d+)\\);", RegexOptions.Compiled)]
    private static partial Regex MetadataVersionRegex();
}
