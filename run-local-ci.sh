#!/usr/bin/env bash
# Mirrors the build-linux job in .github/workflows/main.yml.
# Each matrix entry runs in its own fresh container, matching CI behaviour.
set -euo pipefail

IMAGE="gcem/ci:latest"
REPO="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# name, build_type, cc, cxx, cxxstd
MATRIX=(
  "gcc12_cxx11          Release  gcc-12     g++-12     11"
  "gcc12_cxx11_coverage Coverage gcc-12     g++-12     11"
  "gcc9_cxx14           Release  gcc-9      g++-9      14"
  "gcc10_cxx14          Release  gcc-10     g++-10     14"
  "gcc11_cxx17          Release  gcc-11     g++-11     17"
  "gcc11_cxx20          Release  gcc-11     g++-11     20"
  "clang11_cxx11        Release  clang-11   clang++-11 11"
  "clang11_cxx14        Release  clang-11   clang++-11 14"
  "clang12_cxx14        Release  clang-12   clang++-12 14"
  "clang13_cxx17        Release  clang-13   clang++-13 17"
  "clang14_cxx20        Release  clang-14   clang++-14 20"
  "gcc13_cxx23          Release  gcc-13     g++-13     23"
  "clang16_cxx23        Release  clang-16   clang++-16 2b"
)

PASS=()
FAIL=()

for entry in "${MATRIX[@]}"; do
  read -r name build_type cc cxx cxxstd <<< "$entry"

  echo ""
  echo "-> $name"

  coverage=$([[ "$build_type" == "Coverage" ]] && echo "1" || echo "")

  if docker run --rm -v "${REPO}:/src" -w /src/tests "$IMAGE" bash -c "
    export CC=$cc
    export CXX=$cxx
    export GCEM_CXX_STD=-std=c++$cxxstd
    export COVERAGE=$coverage
    make clean
    make
    ./run_tests
  "; then
    PASS+=("$name")
  else
    FAIL+=("$name")
  fi
done

echo ""
for name in "${PASS[@]}"; do echo "PASS  $name"; done
for name in "${FAIL[@]}"; do echo "FAIL  $name"; done
echo ""

[ ${#FAIL[@]} -eq 0 ]
