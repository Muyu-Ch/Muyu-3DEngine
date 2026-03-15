// main.cpp（测试入口）
#include "Render.h"
#include <iostream>
#include<vector>

int main()
{
    // 创建Render对象，默认800x600窗口
    Render render(1000,1000,100.0f);

    // 初始化（创建窗口）
    if (!render.Init())
    {
        std::cerr << "Render初始化失败！" << std::endl;
        return -1;
    }

    bool isRunning = true;    // 主循环开关
    SDL_Event event; // 事件对象（检测按键/关闭窗口）

    std::vector<Vector3> vectors={
        Vector3(300,300,10),
        Vector3(300,-300,10),
        Vector3 (-300,300,10),
        Vector3(-300,-300,10),
        Vector3(300,300,310),
        Vector3(300,-300,310),
        Vector3(-300,300,310),
        Vector3(-300,-300,310)
    };

     float Dz=1;

    while (isRunning)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT) // 点击窗口关闭按钮
                isRunning = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) // 按ESC
                isRunning = false;
        }


        for (size_t i=0;i<vectors.size();i++)
        {
            vectors[i].z += Dz;
        }

        render.Clear();

        std::vector<std::pair<int,int>>points;

        for (int i=0;i<8;i++)
        {
            int x,y;
            render.Project(vectors[i],x,y);
            points.push_back(std::make_pair(x,y));
        }

        // 画一个5x5的白色方块（方便看）
        for (int i=0;i<8;i++)
        {
            int x=points[i].first;
            int y=points[i].second;
            for (int dx = -4; dx <= 4; dx++)
            {
                for (int dy = -4; dy <= 4; dy++)
                {
                    render.DrawPixel(x+dx,y+dy);
                }
            }
        }

        // 5. 刷新显示（把新画面展示到窗口）
        render.Present();

        // 控制帧率（约60帧/秒，避免画面太快）
        SDL_Delay(16);
    }

    std::cout<<"程序退出"<<std::endl;

    return 0;
}