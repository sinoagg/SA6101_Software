@echo "D:\software\NILWCVI\Shared\MSDTRedistributables\BuildTools\8.1\rc.exe" /d _CVI_ /i "D:\software\NILWCVI\Shared\MSDTRedistributables\SDKHeaderFiles\8.1" /fo %2 %1
@"D:\software\NILWCVI\Shared\MSDTRedistributables\BuildTools\8.1\rc.exe" /d _CVI_ /i "D:\software\NILWCVI\Shared\MSDTRedistributables\SDKHeaderFiles\8.1" /fo %2 %1 > Rc.out 2>&1
@if errorlevel 1 goto err
@echo RC complete
@exit 0
:err
@echo RC failed
@exit 1
