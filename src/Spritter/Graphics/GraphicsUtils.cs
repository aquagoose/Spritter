namespace Spritter.Graphics;

internal static class GraphicsUtils
{
    public static grabs.Graphics.ShaderStage ToGrabs(this ShaderStage stage)
    {
        return stage switch
        {
            ShaderStage.Vertex => grabs.Graphics.ShaderStage.Vertex,
            ShaderStage.Pixel => grabs.Graphics.ShaderStage.Pixel,
            _ => throw new ArgumentOutOfRangeException(nameof(stage), stage, null)
        };
    }
}