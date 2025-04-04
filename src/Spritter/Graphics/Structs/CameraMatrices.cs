using System.Numerics;

namespace Spritter.Graphics.Structs;

public struct CameraMatrices
{
    public const uint SizeInBytes = 128;
    
    public Matrix4x4 Projection;

    public Matrix4x4 View;

    public CameraMatrices(Matrix4x4 projection, Matrix4x4 view)
    {
        Projection = projection;
        View = view;
    }
}