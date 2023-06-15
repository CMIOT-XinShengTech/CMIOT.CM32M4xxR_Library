@echo off

python %~dp0\pic_to_data.py %~dp0\logo.png %~dp0../Application/Source/logo.c
python %~dp0\pic_to_data.py %~dp0\pic1.png %~dp0../Application/Source/pic1.c
python %~dp0\pic_to_data.py %~dp0\pic2.png %~dp0../Application/Source/pic2.c
