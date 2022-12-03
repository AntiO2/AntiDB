## 配置

### Windows

|   工具   |                  版本                   |
| :------: | :-------------------------------------: |
| 构建工具 | cmake version 3.24.3<br/>GNU Make 4.2.1 |
|  编译器  |         gcc version 9.2.0 (GCC)         |
| 版本控制 |      git version 2.34.1.windows.1       |

## 构建方式

### Windows

1. 打开终端，切换工作目录为`AntiDB`
2. 如果没有`build`文件夹，输入`mkdir build`
3. `cd build`，进入build文件夹
4. `cmake ..` 之后，`make`生成目标程序和测试程序
