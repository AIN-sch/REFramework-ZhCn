# RE Framework 中文版

自用汉化。基于 upstream `d4611aef`。

汉化范围是 UI 文本和模组显示名，`src/` 下 41 个文件有改动。

## 用法

`release/RE Framework-ZhCn.zip` 解开，把 `dinput8.dll` 放到游戏 exe 同级目录。

`reframework_revision.txt` 是对应的 upstream 提交，方便对照。

## 源码

`src/`、`shared/`、`csharp-api/` 等是 upstream 原样，只带汉化改动。

`dependencies/` 没打包，那是 submodule，按 `.gitmodules` 自己拉。

编译看 `COMPILING.md`，需要 VS2022 和 CMake。

## 许可

LICENSE 沿用 upstream。
