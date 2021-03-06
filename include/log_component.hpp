#ifndef LOG_COMPONENTS_HPP
#define LOG_COMPONENTS_HPP
#include "components.hpp"

class LogicGate : public Component{
public:
    LogicGate(const std::string &name);

    virtual ~LogicGate() override;

    // From given voltage returns their logical value
    static bool getBoolVoltage(double v);

    void connect(const std::vector<std::pair<int, int>>& connPts) override;

    void disconnect(int x, int y) override;

    void disconnect() override;
#ifdef QTPAINT
	std::vector<std::pair<int, int>> connectionPoints(void) const override;
#endif

protected:
	std::string toString() const override;

#ifdef QTPAINT
    QRectF boundingRect() const override;

    void voltageDependedSetPen(QPainter* painter, unsigned id);
    void voltageDependedDrawLine(QLineF line, QPainter* painter, unsigned id);
#endif
};

class ANDGate : public LogicGate, public Counter<ANDGate>{
public:
    ANDGate();

    std::string componentType() const override { return "and"; }
    
    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class ORGate : public LogicGate, public Counter<ORGate>{
public:
    ORGate();

    std::string componentType() const override { return "or"; }

    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class XORGate : public LogicGate, public Counter<XORGate>{
public:
    XORGate();

    std::string componentType() const override { return "xor"; }

    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class NANDGate : public LogicGate, public Counter<NANDGate>{
public:
    NANDGate();

    std::string componentType() const override { return "nand"; }
    
    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class NORGate : public LogicGate, public Counter<NORGate>{
public:
    NORGate();
    
    std::string componentType() const override { return "nor"; }

    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class NXORGate : public LogicGate, public Counter<NXORGate>{
public:
    NXORGate();
    
    std::string componentType() const override { return "nxor"; }

    double voltage() const override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
#endif

};

class NOTGate: public LogicGate, public Counter<NOTGate> {
public:
    NOTGate();

    ~NOTGate() override;

    std::string componentType() const override { return "not"; }

    double voltage() const override;

    void disconnect(int x, int y) override;

    void disconnect() override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    std::vector<std::pair<int, int>> connectionPoints(void) const override;
#endif

private:
	std::string toString() const override;
};


class JKFlipFlop: public LogicGate, public Counter<JKFlipFlop> {
public:
    JKFlipFlop();

    ~JKFlipFlop() override;

    enum pin {
		J, CLK, K, Q, Qc
    };

    std::string componentType() const override { return "flipflop"; }

    std::string toString() const override;

    double voltage() const override;

    void disconnect(int x, int y) override;

    void disconnect() override;
#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    std::vector<std::pair<int, int>> connectionPoints(void) const override;
protected:
	QRectF boundingRect() const override;
#endif

    void set() const;
    void reset() const;
private:
    mutable bool _old_clk;
};


class Decoder : public LogicGate, public Counter<Decoder> {
public:
    Decoder();
	~Decoder() override;

    std::string componentType() const override { return "decoder"; }

    enum pin {
        I3, I2, I1, I0,
        a, b, c, d, e, f, g
    };

	double voltage() const override;

    void disconnect(int x, int y) override;

    void disconnect() override;

#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    std::vector<std::pair<int, int>> connectionPoints(void) const override;
protected:
	QRectF boundingRect() const override;
#endif

private:
	int  inputToBinaryInt(double a, double b, double c, double d) const;
	void decodeOutput(int input) const;
	void updateVoltages() const;
	std::string toString() const override;
};

class LCDDisplay : public LogicGate, public Counter<LCDDisplay> {
public:
    LCDDisplay();

    ~LCDDisplay() override;

    std::string toString() const override;

    std::string componentType() const override { return "lcd"; }

    enum pin {
        a, b, c, d, e, f, g
    };

    double voltage() const override {
        return 0;
    }

#ifdef QTPAINT
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    std::vector<std::pair<int, int>> connectionPoints(void) const override;
protected:
	QRectF boundingRect() const override;
#endif
};

#endif /* ifndef LOG_COMPONENTS_HPP */
