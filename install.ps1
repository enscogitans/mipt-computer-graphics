param(
    [string]$dst_dir="bin",
    [string]$build_dir="build"
)

mkdir $build_dir -ErrorAction SilentlyContinue
cmake -S . -B $build_dir -DCMAKE_BUILD_TYPE=Release
cmake --build $build_dir --config Release
cmake --install $build_dir --prefix $dst_dir --config Release --component hw1
cmake --install $build_dir --prefix $dst_dir --config Release --component hw2
