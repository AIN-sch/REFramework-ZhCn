# RE Framework 中文版

自用汉化。基于 upstream `d4611aef`（praydog/REFramework）。

汉化范围是 UI 文本和模组显示名，`src/` 下 41 个文件有改动。

## 源码

`src/`、`shared/`、`csharp-api/`、`include/` 等是 upstream 原样，只带汉化改动。

`dependencies/` 已内联进仓库：

- `imguizmo` `imnodes` `lua` `nlohmann` `openvr` `sol2` 是 upstream 的普通目录，直接带入。
- `glm` `imgui` `minhook` `spdlog` 仍是 submodule，取用前必须初始化，否则 CMake 在 `CMakeLists.txt:325` 报
  `file COPY cannot find .../dependencies/openvr/lib/win64/openvr_api.lib`。

## 编译

需要 VS2022（或 VS2026）和 CMake，看 `COMPILING.md`。仓库不提供二进制，自行编译。

```bash
git clone https://github.com/AIN-sch/REFramework-ZhCn
cd REFramework-ZhCn
git submodule update --init --recursive

cmake -S . -B build -G "Visual Studio 18 2026" -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target REFramework
```

产物：`build/bin/REFramework/dinput8.dll`，放到游戏 exe 同级目录。

## 许可

LICENSE 沿用 upstream。
