using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Spritter.Graphics;

public static class GraphicsUtils
{
    public static unsafe ReadOnlySpan<byte> EmptySpan<T>(uint numElements) where T : unmanaged
    {
        uint sizeInBytes = numElements * (uint) sizeof(T);

        return MemoryMarshal.CreateReadOnlySpan(ref Unsafe.NullRef<byte>(), (int) sizeInBytes);
    }

    public static ReadOnlySpan<byte> FromSpan<T>(in ReadOnlySpan<T> span) where T : unmanaged
    {
        return MemoryMarshal.Cast<T, byte>(span);
    }
    
    internal static grabs.Graphics.ShaderStage ToGrabs(this ShaderStage stage)
    {
        return stage switch
        {
            ShaderStage.Vertex => grabs.Graphics.ShaderStage.Vertex,
            ShaderStage.Pixel => grabs.Graphics.ShaderStage.Pixel,
            _ => throw new ArgumentOutOfRangeException(nameof(stage), stage, null)
        };
    }
}