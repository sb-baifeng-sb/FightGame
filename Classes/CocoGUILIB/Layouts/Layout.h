/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "../BaseClasses/UIWidget.h"
#include "LayoutExecutant.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LAYOUT_COLOR_NONE,
    LAYOUT_COLOR_SOLID,
    LAYOUT_COLOR_GRADIENT
}LayoutBackGroundColorType;

class Layout : public UIWidget
{
public:
    /**
     * Default constructor
     */
    Layout();
    
    /**
     * Default destructor
     */
    virtual ~Layout();
    
    /**
     * Allocates and initializes a layout.
     */
    static Layout* create();
    
    /**
     * Sets a LayoutExecutant for doing layout.
     *
     * @see LayoutExecutant
     *
     * @param LayoutExecutant pointer.
     */
    virtual void setLayoutExecutant(LayoutExecutant* exe);
    
    /**
     * Gets the LayoutExecutant of Layout
     *
     * @see LayoutExecutant
     *
     * @return LayoutExecutant pointer.
     */
    virtual LayoutExecutant* getLayoutExecutant() const;
    
    //override "hitTest" method of widget.
    virtual bool hitTest(const Point &pt);
    
    //background
    /**
     * Sets a background image for layout
     *
     * @param fileName image file path.
     *
     * @param texType @see TextureResType. UI_TEX_TYPE_LOCAL means local file, UI_TEX_TYPE_PLIST means sprite frame.
     */
    void setBackGroundImage(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    
    /**
     * Sets a background image capinsets for layout, if the background image is a scale9 render.
     *
     * @param capinsets of background image.
     *
     */
    void setBackGroundImageCapInsets(const Rect& capInsets);
    
    /**
     * Sets Color Type for layout.
     *
     * @param type   @see LayoutBackGroundColorType.
     */
    void setBackGroundColorType(LayoutBackGroundColorType type);
    
    /**
     * Sets background iamge use scale9 renderer.
     *
     * @param enabled   true that use scale9 renderer, false otherwise.
     */
    void setBackGroundImageScale9Enabled(bool enabled);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_SOLID
     *
     * @param color
     */
    void setBackGroundColor(const Color3B &color);
    
    /**
     * Sets background color for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param start color
     *
     * @param end color
     */
    void setBackGroundColor(const Color3B &startColor, const Color3B &endColor);
    
    /**
     * Sets background opacity layout.
     *
     * @param opacity
     */
    void setBackGroundColorOpacity(int opacity);
    
    /**
     * Sets background color vector for layout, if color type is LAYOUT_COLOR_GRADIENT
     *
     * @param vector
     */
    void setBackGroundColorVector(const Point &vector);
    
    //override "setColor" method of widget.
    virtual void setColor(const Color3B &color);
    
    //override "setOpacity" method of widget.
    virtual void setOpacity(int opacity);
    
    /**
     * Remove the background image of layout.
     */
    void removeBackGroundImage();
    
    /**
     * Gets background image texture size.
     *
     * @return background image texture size.
     */
    const Size& getBackGroundImageTextureSize() const;
    
    /**
     * Changes if layout can clip it's content and child.
     *
     * If you really need this, please enable it. But it would reduce the rendering efficiency. 
     *
     * @param clipping enabled.
     */
    virtual void setClippingEnabled(bool able);
    
    /**
     * Gets if layout is clipping enabled.
     *
     * @return if layout is clipping enabled.
     */
    virtual bool isClippingEnabled();
    
    
    /*Compatible*/
    CC_DEPRECATED_ATTRIBUTE void setBackGroundImageScale9Enable(bool is){setBackGroundImageScale9Enabled(is);};
    CC_DEPRECATED_ATTRIBUTE virtual void setClippingEnable(bool is){setClippingEnabled(is);};
    /************/

protected:
    //override "init" method of widget.
    virtual bool init();
    
    //override "initRenderer" method of widget.
    virtual void initRenderer();
    
    //override "onSizeChanged" method of widget.
    virtual void onSizeChanged();
    
    //init background image renderer.
    void addBackGroundImage();
protected:
    bool m_bClippingEnabled;
    LayoutExecutant* m_pLayoutExecutant;
    
    //background
    bool m_bBackGroundScale9Enable;
    Node* m_pBackGroundImage;
    std::string m_strBackGroundImageFileName;
    Rect m_backGroundImageCapInsets;
    LayoutBackGroundColorType m_colorType;
    TextureResType m_eBGImageTexType;
    LayerColor* m_pColorRender;
    LayerGradient* m_pGradientRender;
    Color3B m_cColor;
    Color3B m_gStartColor;
    Color3B m_gEndColor;
    Point m_AlongVector;
    int m_nCOpacity;
    Size m_backGroundImageTextureSize;
};

class RectClippingNode : public ClippingNode
{
public:
    virtual ~RectClippingNode();
    virtual bool init();
    static RectClippingNode* create();
    void setClippingSize(const Size& size);
    void setClippingEnabled(bool enabled);
    virtual void visit();
protected:
    DrawNode* m_pInnerStencil;
private:
    RectClippingNode();
    Point rect[4];
    Size m_clippingSize;
    bool m_bClippingEnabled;
};

NS_CC_EXT_END

#endif /* defined(__Layout__) */
