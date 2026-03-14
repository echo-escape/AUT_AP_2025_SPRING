#include "Q3_Count_Islands.h"

// 修复一：辅助函数必须写在调用它的主函数上方（或在头部提前声明）
// 参数 grid 不带 const，且带有 &（引用），这意味着我们直接在原图（或可修改的副本）上填海造陆
void sinkIsland(std::vector<std::vector<int>>& grid, int r, int c) {
    
    // 进门第一件事：把当前踩到的这块陆地沉入海底（变成 0）
    grid[r][c] = 0;

    // 定义四个方向的坐标偏移量：上(-1, 0)，下(1, 0)，左(0, -1)，右(0, 1)
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 采用 int 转换避免有符号/无符号整数比对时的编译器警告
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < 4; i++) {
        int nextRow = r + dirs[i][0];
        int nextCol = c + dirs[i][1];

        // 边界安全检查：如果越界，直接【跳过】这个方向，看下一个方向
        if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) {
            continue; 
        }

        // 修复二：如果下一个格子是 1（陆地），继续顺藤摸瓜进行 DFS
        // 注意：这里去掉了你原本的 if (grid == 0) return; 否则遇到海水会直接断掉整个方向探测
        if (grid[nextRow][nextCol] == 1) {
            sinkIsland(grid, nextRow, nextCol); // 递归调用自己
        }
    }
}

// 主函数
int count_islands(const std::vector<std::vector<int>>& grid) {
    
    // 边界情况 1：空网格直接返回（严谨拦截第一行也为空的情况）
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }

    // 修复三：突破 const 限制
    // 因为传入的 grid 是 const (只读的)，直接修改会引发编译报错
    // 我们必须拷贝一份副本，在副本上使用“油漆桶”填色
    std::vector<std::vector<int>> map_copy = grid;
    
    int count = 0;
    int rows = map_copy.size();
    int cols = map_copy[0].size();

    // 遍历整个网格寻找新的岛屿
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            
            // 如果在副本中发现了一块新的陆地
            if (map_copy[i][j] == 1) {
                count++;  // 岛屿总数 +1
                // 立刻把这块陆地及与其相连的所有陆地全部“击沉”为 0
                sinkIsland(map_copy, i, j); 
            }
        }
    }

    return count;
}