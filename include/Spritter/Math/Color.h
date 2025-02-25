#pragma once

#include <cstdint>

namespace Spritter::Math
{
    struct Color
    {
        float R;
        float G;
        float B;
        float A;

        Color()
        {
            R = 0;
            G = 0;
            B = 0;
            A = 0;
        }

        Color(const float r, const float g, const float b, const float a = 1.0f)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = UINT8_MAX)
        {
            constexpr float multiplier = 1.0f / static_cast<float>(UINT8_MAX);

            R = static_cast<float>(r) * multiplier;
            G = static_cast<float>(g) * multiplier;
            B = static_cast<float>(b) * multiplier;
            A = static_cast<float>(a) * multiplier;
        }

        static Color AliceBlue() { return { 0.9411764705882353f, 0.9725490196078431f, 1.0f }; }

        static Color AntiqueWhite() { return { 0.9803921568627451f, 0.9215686274509803f, 0.8431372549019608f }; }

        static Color Aqua() { return { 0.0f, 1.0f, 1.0f }; }

        static Color Aquamarine() { return { 0.4980392156862745f, 1.0f, 0.8313725490196079f }; }

        static Color Azure() { return { 0.9411764705882353f, 1.0f, 1.0f }; }

        static Color Beige() { return { 0.9607843137254902f, 0.9607843137254902f, 0.8627450980392157f }; }

        static Color Bisque() { return { 1.0f, 0.8941176470588236f, 0.7686274509803922f }; }

        static Color Black() { return { 0.0f, 0.0f, 0.0f }; }

        static Color BlanchedAlmond() { return { 1.0f, 0.9215686274509803f, 0.803921568627451f }; }

        static Color Blue() { return { 0.0f, 0.0f, 1.0f }; }

        static Color BlueViolet() { return { 0.5411764705882353f, 0.16862745098039217f, 0.8862745098039215f }; }

        static Color Brown() { return { 0.6470588235294118f, 0.16470588235294117f, 0.16470588235294117f }; }

        static Color BurlyWood() { return { 0.8705882352941177f, 0.7215686274509804f, 0.5294117647058824f }; }

        static Color CadetBlue() { return { 0.37254901960784315f, 0.6196078431372549f, 0.6274509803921569f }; }

        static Color Chartreuse() { return { 0.4980392156862745f, 1.0f, 0.0f }; }

        static Color Chocolate() { return { 0.8235294117647058f, 0.4117647058823529f, 0.11764705882352941f }; }

        static Color Coral() { return { 1.0f, 0.4980392156862745f, 0.3137254901960784f }; }

        static Color CornflowerBlue() { return { 0.39215686274509803f, 0.5843137254901961f, 0.9294117647058824f }; }

        static Color Cornsilk() { return { 1.0f, 0.9725490196078431f, 0.8627450980392157f }; }

        static Color Crimson() { return { 0.8627450980392157f, 0.0784313725490196f, 0.23529411764705882f }; }

        static Color Cyan() { return { 0.0f, 1.0f, 1.0f }; }

        static Color DarkBlue() { return { 0.0f, 0.0f, 0.5450980392156862f }; }

        static Color DarkCyan() { return { 0.0f, 0.5450980392156862f, 0.5450980392156862f }; }

        static Color DarkGoldenRod() { return { 0.7215686274509804f, 0.5254901960784314f, 0.043137254901960784f }; }

        static Color DarkGray() { return { 0.6627450980392157f, 0.6627450980392157f, 0.6627450980392157f }; }

        static Color DarkGrey() { return { 0.6627450980392157f, 0.6627450980392157f, 0.6627450980392157f }; }

        static Color DarkGreen() { return { 0.0f, 0.39215686274509803f, 0.0f }; }

        static Color DarkKhaki() { return { 0.7411764705882353f, 0.7176470588235294f, 0.4196078431372549f }; }

        static Color DarkMagenta() { return { 0.5450980392156862f, 0.0f, 0.5450980392156862f }; }

        static Color DarkOliveGreen() { return { 0.3333333333333333f, 0.4196078431372549f, 0.1843137254901961f }; }

        static Color DarkOrange() { return { 1.0f, 0.5490196078431373f, 0.0f }; }

        static Color DarkOrchid() { return { 0.6f, 0.19607843137254902f, 0.8f }; }

        static Color DarkRed() { return { 0.5450980392156862f, 0.0f, 0.0f }; }

        static Color DarkSalmon() { return { 0.9137254901960784f, 0.5882352941176471f, 0.47843137254901963f }; }

        static Color DarkSeaGreen() { return { 0.5607843137254902f, 0.7372549019607844f, 0.5607843137254902f }; }

        static Color DarkSlateBlue() { return { 0.2823529411764706f, 0.23921568627450981f, 0.5450980392156862f }; }

        static Color DarkSlateGray() { return { 0.1843137254901961f, 0.30980392156862746f, 0.30980392156862746f }; }

        static Color DarkSlateGrey() { return { 0.1843137254901961f, 0.30980392156862746f, 0.30980392156862746f }; }

        static Color DarkTurquoise() { return { 0.0f, 0.807843137254902f, 0.8196078431372549f }; }

        static Color DarkViolet() { return { 0.5803921568627451f, 0.0f, 0.8274509803921568f }; }

        static Color DeepPink() { return { 1.0f, 0.0784313725490196f, 0.5764705882352941f }; }

        static Color DeepSkyBlue() { return { 0.0f, 0.7490196078431373f, 1.0f }; }

        static Color DimGray() { return { 0.4117647058823529f, 0.4117647058823529f, 0.4117647058823529f }; }

        static Color DimGrey() { return { 0.4117647058823529f, 0.4117647058823529f, 0.4117647058823529f }; }

        static Color DodgerBlue() { return { 0.11764705882352941f, 0.5647058823529412f, 1.0f }; }

        static Color FireBrick() { return { 0.6980392156862745f, 0.13333333333333333f, 0.13333333333333333f }; }

        static Color FloralWhite() { return { 1.0f, 0.9803921568627451f, 0.9411764705882353f }; }

        static Color ForestGreen() { return { 0.13333333333333333f, 0.5450980392156862f, 0.13333333333333333f }; }

        static Color Fuchsia() { return { 1.0f, 0.0f, 1.0f }; }

        static Color Gainsboro() { return { 0.8627450980392157f, 0.8627450980392157f, 0.8627450980392157f }; }

        static Color GhostWhite() { return { 0.9725490196078431f, 0.9725490196078431f, 1.0f }; }

        static Color Gold() { return { 1.0f, 0.8431372549019608f, 0.0f }; }

        static Color GoldenRod() { return { 0.8549019607843137f, 0.6470588235294118f, 0.12549019607843137f }; }

        static Color Gray() { return { 0.5019607843137255f, 0.5019607843137255f, 0.5019607843137255f }; }

        static Color Grey() { return { 0.5019607843137255f, 0.5019607843137255f, 0.5019607843137255f }; }

        static Color Green() { return { 0.0f, 0.5019607843137255f, 0.0f }; }

        static Color GreenYellow() { return { 0.6784313725490196f, 1.0f, 0.1843137254901961f }; }

        static Color HoneyDew() { return { 0.9411764705882353f, 1.0f, 0.9411764705882353f }; }

        static Color HotPink() { return { 1.0f, 0.4117647058823529f, 0.7058823529411765f }; }

        static Color IndianRed() { return { 0.803921568627451f, 0.3607843137254902f, 0.3607843137254902f }; }

        static Color Indigo() { return { 0.29411764705882354f, 0.0f, 0.5098039215686274f }; }

        static Color Ivory() { return { 1.0f, 1.0f, 0.9411764705882353f }; }

        static Color Khaki() { return { 0.9411764705882353f, 0.9019607843137255f, 0.5490196078431373f }; }

        static Color Lavender() { return { 0.9019607843137255f, 0.9019607843137255f, 0.9803921568627451f }; }

        static Color LavenderBlush() { return { 1.0f, 0.9411764705882353f, 0.9607843137254902f }; }

        static Color LawnGreen() { return { 0.48627450980392156f, 0.9882352941176471f, 0.0f }; }

        static Color LemonChiffon() { return { 1.0f, 0.9803921568627451f, 0.803921568627451f }; }

        static Color LightBlue() { return { 0.6784313725490196f, 0.8470588235294118f, 0.9019607843137255f }; }

        static Color LightCoral() { return { 0.9411764705882353f, 0.5019607843137255f, 0.5019607843137255f }; }

        static Color LightCyan() { return { 0.8784313725490196f, 1.0f, 1.0f }; }

        static Color LightGoldenRodYellow() { return { 0.9803921568627451f, 0.9803921568627451f, 0.8235294117647058f }; }

        static Color LightGray() { return { 0.8274509803921568f, 0.8274509803921568f, 0.8274509803921568f }; }

        static Color LightGrey() { return { 0.8274509803921568f, 0.8274509803921568f, 0.8274509803921568f }; }

        static Color LightGreen() { return { 0.5647058823529412f, 0.9333333333333333f, 0.5647058823529412f }; }

        static Color LightPink() { return { 1.0f, 0.7137254901960784f, 0.7568627450980392f }; }

        static Color LightSalmon() { return { 1.0f, 0.6274509803921569f, 0.47843137254901963f }; }

        static Color LightSeaGreen() { return { 0.12549019607843137f, 0.6980392156862745f, 0.6666666666666666f }; }

        static Color LightSkyBlue() { return { 0.5294117647058824f, 0.807843137254902f, 0.9803921568627451f }; }

        static Color LightSlateGray() { return { 0.4666666666666667f, 0.5333333333333333f, 0.6f }; }

        static Color LightSlateGrey() { return { 0.4666666666666667f, 0.5333333333333333f, 0.6f }; }

        static Color LightSteelBlue() { return { 0.6901960784313725f, 0.7686274509803922f, 0.8705882352941177f }; }

        static Color LightYellow() { return { 1.0f, 1.0f, 0.8784313725490196f }; }

        static Color Lime() { return { 0.0f, 1.0f, 0.0f }; }

        static Color LimeGreen() { return { 0.19607843137254902f, 0.803921568627451f, 0.19607843137254902f }; }

        static Color Linen() { return { 0.9803921568627451f, 0.9411764705882353f, 0.9019607843137255f }; }

        static Color Magenta() { return { 1.0f, 0.0f, 1.0f }; }

        static Color Maroon() { return { 0.5019607843137255f, 0.0f, 0.0f }; }

        static Color MediumAquaMarine() { return { 0.4f, 0.803921568627451f, 0.6666666666666666f }; }

        static Color MediumBlue() { return { 0.0f, 0.0f, 0.803921568627451f }; }

        static Color MediumOrchid() { return { 0.7294117647058823f, 0.3333333333333333f, 0.8274509803921568f }; }

        static Color MediumPurple() { return { 0.5764705882352941f, 0.4392156862745098f, 0.8588235294117647f }; }

        static Color MediumSeaGreen() { return { 0.23529411764705882f, 0.7019607843137254f, 0.44313725490196076f }; }

        static Color MediumSlateBlue() { return { 0.4823529411764706f, 0.40784313725490196f, 0.9333333333333333f }; }

        static Color MediumSpringGreen() { return { 0.0f, 0.9803921568627451f, 0.6039215686274509f }; }

        static Color MediumTurquoise() { return { 0.2823529411764706f, 0.8196078431372549f, 0.8f }; }

        static Color MediumVioletRed() { return { 0.7803921568627451f, 0.08235294117647059f, 0.5215686274509804f }; }

        static Color MidnightBlue() { return { 0.09803921568627451f, 0.09803921568627451f, 0.4392156862745098f }; }

        static Color MintCream() { return { 0.9607843137254902f, 1.0f, 0.9803921568627451f }; }

        static Color MistyRose() { return { 1.0f, 0.8941176470588236f, 0.8823529411764706f }; }

        static Color Moccasin() { return { 1.0f, 0.8941176470588236f, 0.7098039215686275f }; }

        static Color NavajoWhite() { return { 1.0f, 0.8705882352941177f, 0.6784313725490196f }; }

        static Color Navy() { return { 0.0f, 0.0f, 0.5019607843137255f }; }

        static Color OldLace() { return { 0.9921568627450981f, 0.9607843137254902f, 0.9019607843137255f }; }

        static Color Olive() { return { 0.5019607843137255f, 0.5019607843137255f, 0.0f }; }

        static Color OliveDrab() { return { 0.4196078431372549f, 0.5568627450980392f, 0.13725490196078433f }; }

        static Color Orange() { return { 1.0f, 0.6470588235294118f, 0.0f }; }

        static Color OrangeRed() { return { 1.0f, 0.27058823529411763f, 0.0f }; }

        static Color Orchid() { return { 0.8549019607843137f, 0.4392156862745098f, 0.8392156862745098f }; }

        static Color PaleGoldenRod() { return { 0.9333333333333333f, 0.9098039215686274f, 0.6666666666666666f }; }

        static Color PaleGreen() { return { 0.596078431372549f, 0.984313725490196f, 0.596078431372549f }; }

        static Color PaleTurquoise() { return { 0.6862745098039216f, 0.9333333333333333f, 0.9333333333333333f }; }

        static Color PaleVioletRed() { return { 0.8588235294117647f, 0.4392156862745098f, 0.5764705882352941f }; }

        static Color PapayaWhip() { return { 1.0f, 0.9372549019607843f, 0.8352941176470589f }; }

        static Color PeachPuff() { return { 1.0f, 0.8549019607843137f, 0.7254901960784313f }; }

        static Color Peru() { return { 0.803921568627451f, 0.5215686274509804f, 0.24705882352941178f }; }

        static Color Pink() { return { 1.0f, 0.7529411764705882f, 0.796078431372549f }; }

        static Color Plum() { return { 0.8666666666666667f, 0.6274509803921569f, 0.8666666666666667f }; }

        static Color PowderBlue() { return { 0.6901960784313725f, 0.8784313725490196f, 0.9019607843137255f }; }

        static Color Purple() { return { 0.5019607843137255f, 0.0f, 0.5019607843137255f }; }

        static Color RebeccaPurple() { return { 0.4f, 0.2f, 0.6f }; }

        static Color Red() { return { 1.0f, 0.0f, 0.0f }; }

        static Color RosyBrown() { return { 0.7372549019607844f, 0.5607843137254902f, 0.5607843137254902f }; }

        static Color RoyalBlue() { return { 0.2549019607843137f, 0.4117647058823529f, 0.8823529411764706f }; }

        static Color SaddleBrown() { return { 0.5450980392156862f, 0.27058823529411763f, 0.07450980392156863f }; }

        static Color Salmon() { return { 0.9803921568627451f, 0.5019607843137255f, 0.4470588235294118f }; }

        static Color SandyBrown() { return { 0.9568627450980393f, 0.6431372549019608f, 0.3764705882352941f }; }

        static Color SeaGreen() { return { 0.1803921568627451f, 0.5450980392156862f, 0.3411764705882353f }; }

        static Color SeaShell() { return { 1.0f, 0.9607843137254902f, 0.9333333333333333f }; }

        static Color Sienna() { return { 0.6274509803921569f, 0.3215686274509804f, 0.17647058823529413f }; }

        static Color Silver() { return { 0.7529411764705882f, 0.7529411764705882f, 0.7529411764705882f }; }

        static Color SkyBlue() { return { 0.5294117647058824f, 0.807843137254902f, 0.9215686274509803f }; }

        static Color SlateBlue() { return { 0.41568627450980394f, 0.35294117647058826f, 0.803921568627451f }; }

        static Color SlateGray() { return { 0.4392156862745098f, 0.5019607843137255f, 0.5647058823529412f }; }

        static Color SlateGrey() { return { 0.4392156862745098f, 0.5019607843137255f, 0.5647058823529412f }; }

        static Color Snow() { return { 1.0f, 0.9803921568627451f, 0.9803921568627451f }; }

        static Color SpringGreen() { return { 0.0f, 1.0f, 0.4980392156862745f }; }

        static Color SteelBlue() { return { 0.27450980392156865f, 0.5098039215686274f, 0.7058823529411765f }; }

        static Color Tan() { return { 0.8235294117647058f, 0.7058823529411765f, 0.5490196078431373f }; }

        static Color Teal() { return { 0.0f, 0.5019607843137255f, 0.5019607843137255f }; }

        static Color Thistle() { return { 0.8470588235294118f, 0.7490196078431373f, 0.8470588235294118f }; }

        static Color Tomato() { return { 1.0f, 0.38823529411764707f, 0.2784313725490196f }; }

        static Color Turquoise() { return { 0.25098039215686274f, 0.8784313725490196f, 0.8156862745098039f }; }

        static Color Violet() { return { 0.9333333333333333f, 0.5098039215686274f, 0.9333333333333333f }; }

        static Color Wheat() { return { 0.9607843137254902f, 0.8705882352941177f, 0.7019607843137254f }; }

        static Color White() { return { 1.0f, 1.0f, 1.0f }; }

        static Color WhiteSmoke() { return { 0.9607843137254902f, 0.9607843137254902f, 0.9607843137254902f }; }

        static Color Yellow() { return { 1.0f, 1.0f, 0.0f }; }

        static Color YellowGreen() { return { 0.6039215686274509f, 0.803921568627451f, 0.19607843137254902f }; }

        static Color Transparent() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
    };
}