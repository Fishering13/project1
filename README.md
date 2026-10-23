# Лабораторная работа №2 — arraylib

Чиранов А. А., ИУ5-13/4, 2026.

Калькулятор массива `int`: `arr_sum`, `arr_max`, `arr_min`, `arr_average`,
`arr_count_positive`, `arr_count_negative`, `arr_count_zero`, `arr_product`, `arr_median`.
Размер передаётся как `size_t`; массив непустой, указатель валиден.
Сумма и произведение должны быть представимы в `int`. Медиана сортирует копию,
не изменяя исходный массив; среднее и медиана возвращают `double`.
Для суммы используется аккумулятор `long long` (частичные суммы должны помещаться в него).

## Сборка в WSL Ubuntu

```sh
cmake -S . -B build-lab2 -DCMAKE_BUILD_TYPE=Release
cmake --build build-lab2 --parallel
ctest --test-dir build-lab2 --output-on-failure
./build-lab2/bin/app
./build-lab2/bin/app_static
ldd build-lab2/bin/app
ar t build-lab2/lib/libarraylib.a
```

`bin/libarraylib.so` — динамическая библиотека; `lib/libarraylib.a` — статическая.
RPATH `$ORIGIN` позволяет находить `.so` рядом с программой.
На Windows CMake создаёт DLL и её import library; статическая библиотека хранится
в отдельном каталоге `lib`. Для Visual Studio используйте `--config Release`
при сборке и `-C Release` для CTest. CI выполняет сборку и тесты на Ubuntu и Windows.

## Структура

- `include/arraylib.h` — интерфейс и экспорт DLL.
- `src/arraylib.cpp` — реализация девяти функций.
- `main.cpp` — демонстрация всех функций.
- `stages/01_monolithic.cpp` — самодостаточная программа первого этапа.
- `tests/` — unit- и интеграционные проверки; assert включён и в Release.
- `.github/workflows/ci.yml` — автоматическая сборка Linux/Windows.
- `src/main.cpp` — сохранённый код предыдущей лабораторной, не входит в новые цели.

## Ручные этапы

```sh
mkdir -p build-lab2/manual
g++ -std=c++17 stages/01_monolithic.cpp -o build-lab2/manual/app_monolithic
g++ -std=c++17 -Iinclude main.cpp src/arraylib.cpp -o build-lab2/manual/app_modules
g++ -std=c++17 -DARRAYLIB_STATIC -Iinclude -c src/arraylib.cpp -o build-lab2/manual/arraylib.o
ar rcs build-lab2/manual/libarraylib.a build-lab2/manual/arraylib.o
g++ -std=c++17 -DARRAYLIB_STATIC -Iinclude main.cpp build-lab2/manual/libarraylib.a -o build-lab2/manual/app_static
g++ -std=c++17 -fPIC -DARRAYLIB_BUILD -Iinclude -c src/arraylib.cpp -o build-lab2/manual/arraylib_pic.o
g++ -shared -o build-lab2/manual/libarraylib.so build-lab2/manual/arraylib_pic.o
g++ -std=c++17 -Iinclude main.cpp -Lbuild-lab2/manual -larraylib -o build-lab2/manual/app_shared
LD_LIBRARY_PATH=build-lab2/manual ./build-lab2/manual/app_shared
```

История содержит этапы реализации, feature-ветку с тестами медианы и merge-коммит.

## Вариант 29 — надой молока

Демонстратор `examples/variant_29.cpp` написан на C++17 и использует динамическую библиотеку.
Запуск: `./build-lab2/bin/variant_29`. Средний надой 132.70, общий объём 1327,
минимум 119, максимум 147, медиана 133.00. Все показатели проверяет CTest.
