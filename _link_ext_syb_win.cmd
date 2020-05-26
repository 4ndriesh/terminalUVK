
set MVP_ROOT_PATH=..\..\..
echo %MVP_ROOT_PATH%
mklink /d .\libs\mvp_classes  %MVP_ROOT_PATH%\mvp_classes
mklink /d  .\libs\common_src  %MVP_ROOT_PATH%\common_src
