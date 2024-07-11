/////////////////////////////////////////////////////////////
// Tree
// Platform	: Visual Studio 2022 (v143), EasyX_20240225
// Author	: 872289455@qq.com
// Date		: 2024-03-17
//

#pragma warning(disable:4305)
#pragma warning(disable:4244)

#define _USE_MATH_DEFINES
#include <random>
#include <queue>
#include <thread>
#include <easyx.h>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr float OFF_SET[] = { -M_PI / 6.f, -M_PI / 16.f, M_PI / 16.f, M_PI / 6.f };
constexpr float LENGTH[] = { 0.75f, 0.95f, 0.95f, 0.75f };

struct BranchInfo {
    float x, y;
    float length; // 长度 
    float radians; // 弧度 
    float thickness; // 厚度 
    int level;
};

float RandomNum(float min, float max) {
    static std::mt19937 rand_num(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rand_num);
}

void ReDraw() {
    cleardevice();
    std::queue<BranchInfo> branches({ 
        BranchInfo{
            WIDTH / 2, // x 坐标为宽度的一半 
            HEIGHT, // y 坐标为高度，即顶部中心点 
            100, // 长度 100  
            -M_PI_2, // - 1/2 pi 弧度 
            8.f, 1 // 厚度8，等级1 
        } 
    });
    // 初始化一个队列 

    // 队列不空，则不停地绘制   
    while (!branches.empty()) {
        const auto &branch = branches.front();

        // 1/2 pi 弧度 等于垂直线 
        float dx = std::cosf(branch.radians); // 余弦值 cos(θ) 是 x 坐标
        float dy = std::sinf(branch.radians); // 正弦值 sin(θ) 是 y 坐标
        float x_end = branch.x + branch.length * dx; // 终点的 x 坐标
        float y_end = branch.y + branch.length * dy; // 终点的 y 坐标

        setlinestyle(PS_SOLID, branch.thickness); // 设置线宽
        // 线的颜色，h 色调 s 饱和度 v 明度
        setlinecolor(HSVtoRGB(15, 0.75, 0.4 + branch.level * 0.05)); // level 增加则明度增加 
        line(branch.x, branch.y, x_end, y_end); // 开始画线 

        // 8 乘以 0.75 要 5 轮才能达到 <= 2
        if (branch.thickness > 2) { // 厚度大于2 说明是树干     
            for (int i = 0; i < 4; i++)
                branches.push({ 
                    x_end, y_end, // 从终点开始 
                    branch.length * LENGTH[i], // 长度 0.75,0.95,0.95,0.75  
                    branch.radians + OFF_SET[i], // 角度 - 1/6pi, - 1/16pi, 1/16pi, 1/6pi 
                    branch.thickness * 0.75f, // 厚度递减 0.75 
                    branch.level + 1 // 增加明度 
                });
        }
        else {
            COLORREF  color = HSVtoRGB(RandomNum(300, 350), RandomNum(0.2, 0.3), 1);
            setlinecolor(color);
            setfillcolor(color);
            dx = RandomNum(-16.f, 16.f);
            dy = RandomNum(-16.f, 16.f);

            // 计算偏移量 (dx, dy) 的欧几里得距离，使用 min(15.f, ...) 将这个距离限制在 15 以内。
            // 用 16 减去这个距离，得到一个从 1 到 16 的值，最后除以 16，将其归一化到 [0, 1] 之间 
            // 根据距离中心点的远近（距离越近，半径越大），确定叶子的大小。
            // 这样可以确保树叶的大小随位置变化而变化，中心附近的叶子较大，远离中心的叶子较小。
            float r = (16.f - min(15.f, std::sqrtf(dx * dx + dy * dy))) / 16.f;

            // 绘制一个填充的圆形。圆心坐标为 (x_end + dx, y_end + dy)，即在分支终点 x_end, y_end 的基础上加上随机偏移量 dx 和 dy
            // 圆的半径为 max(r * 5.f, 1.f)。这里 r 的取值范围是 [0, 1]，乘以 5 后的范围是 [0, 5]。
            // max(r * 5.f, 1.f) 确保半径至少为 1，不会小于 1。
            fillcircle(x_end + dx, y_end + dy, max(r * 5.f, 1.f));
        }
        branches.pop();
        FlushBatchDraw();
    }
}

int main() {
    initgraph(WIDTH, HEIGHT); // 宽800，高600 
    setbkcolor(RGB(255, 255, 255)); // 设置背景颜色 
    BeginBatchDraw(); // 开启批量绘制模式 
    ReDraw(); // 桃树绘制主逻辑 
    while (true) {
        ExMessage msg;
        while (peekmessage(&msg)) {
            if (WM_LBUTTONDOWN == msg.message) {
                ReDraw();
            }
        }
    }
    return 0;
}