using System.Text.Json.Serialization;

namespace Archiver;

public record CaddyIndexFile(
    [property: JsonPropertyName("name")] string Name,
    [property: JsonPropertyName("size")] long Size,
    [property: JsonPropertyName("url")] string Url,
    [property: JsonPropertyName("mod_time")] DateTimeOffset ModificationTime,
    [property: JsonPropertyName("mode")] ushort Mode,
    [property: JsonPropertyName("is_dir")] bool IsDirectory,
    [property: JsonPropertyName("is_symlink")] bool IsSymlink
);
