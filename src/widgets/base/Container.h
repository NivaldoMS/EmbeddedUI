class UIContainer : public UIWidget
{
public:

    virtual bool addChild(UIWidget* child);

    virtual bool removeChild(UIWidget* child);

    virtual uint16_t childCount() const;

    virtual UIWidget* child(uint16_t index);

protected:

    // por enquanto use um array simples.
    // depois substituiremos pelo container definitivo.
};