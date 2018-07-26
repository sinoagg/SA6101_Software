<<<<<<< HEAD
@"c:\program files (x86)\national instruments\cvi2017\bin\cvilink.exe" -cmd:link_options.txt -flags:0 -expiry:0 > Link.out 2>&1
=======
@"d:\software\nilwcvi\nilwcvi2017\bin\cvilink.exe" -cmd:link_options.txt -flags:0 -expiry:0 > Link.out 2>&1
>>>>>>> c470c37cb1316d04d8132fad4521adc588b849fd
@if errorlevel 1 goto err
@echo Link success
@echo Link complete
@exit 0
:err
@echo Link complete
@echo Link failed
@exit 1
