#include <iostream>
#include <vector>

using namespace std;

// ==========================================
// 1. 框架层：父类 (由“过去”的人编写)
// ==========================================
enum ImageType { LAST, SPOT }; // 模拟未来可能出现的不同形状/图像类型

class Image {
public:
    virtual ~Image() {}
    
    // 核心：虚拟构造函数（分身术）
    virtual Image* clone() = 0;
    virtual void draw() = 0;

    // 框架提供的“注册中心”
    // 这里的 static 函数让老代码能根据类型找到并克隆新对象
    static void addPrototype(Image* image) {
        _prototypes.push_back(image);
    }

    static Image* findAndClone(ImageType type) {
        // 关键点：框架在这里寻找样板并“复印”
        for (auto p : _prototypes) {
            if (p->returnType() == type) return p->clone();
        }
        return nullptr;
    }

protected:
    virtual ImageType returnType() = 0;

private:
    // 全局名单：存放所有子类送来的“样板”
    static vector<Image*> _prototypes;
};

// 静态成员初始化（必须在类外定义）
vector<Image*> Image::_prototypes;


// ==========================================
// 2. 应用层：子类 (由“未来”的人编写)
// ==========================================

class LandSatImage : public Image {
private:
    // 【关键点 A】：静态样板对象。它是该类在程序中的“种子”
    static LandSatImage _landSatImage;

    // 【构造函数 1】：专门给静态样板“自荐/挂号”用
    // 设为私有，防止外界乱用
    LandSatImage() {
        cout << "LandSatImage: 种子对象出生，正在向框架注册..." << endl;
        addPrototype(this); 
    }

    // 【构造函数 2】：专门给 clone() 用，避开注册逻辑
    // 这里的 int dummy 只是为了和构造函数 1 做区分（Overload）
    LandSatImage(int dummy) {
        // 这里进行真正的业务数据初始化
    }

protected:
    ImageType returnType() override { return LAST; }

public:
    // 【核心实现】：变相的 new
    Image* clone() override {
        // 这里调用构造函数 2，产生一个纯净的副本
        return new LandSatImage(1); 
    }

    void draw() override {
        cout << "Drawing LandSatImage: 成功通过原型克隆并绘制！" << endl;
    }
};

// 【打火石】：这一行确保 LandSatImage 在 main 运行前就完成了注册
LandSatImage LandSatImage::_landSatImage;


// ==========================================
// 3. 运行层：演示 (体现解耦)
// ==========================================
int main() {
    cout << "--- 程序启动 ---" << endl;

    // 演示重点：
    // 我们在这里完全没有写 "new LandSatImage()"
    // 即使未来增加了新的子类，这里的逻辑也一行都不用改
    
    cout << "正在向框架申请一个 LAST 类型的对象..." << endl;
    Image* myImage = Image::findAndClone(LAST);

    if (myImage) {
        myImage->draw();
        delete myImage;
    } else {
        cout << "错误：未找到对应类型的样板。" << endl;
    }

    return 0;
}