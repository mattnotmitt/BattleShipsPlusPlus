Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
  TermOx
  GIT_REPOSITORY https://github.com/a-n-t-h-o-n-y/TermOx.git
  GIT_TAG        v0.4)

FetchContent_MakeAvailable(TermOx)
