git clone -b v8.3.4 --recursive https://github.com/lvgl/lvgl.git

REQUIRES "esp_timer"



Clone lvgl in "components/"

idf menuconfig:

​	close building example

​	open building demo benchmark and wigets

​    close the first option "pass ... check..." shit

cp "lv_conf_temp.h" as "lv_conf.h" next to "lvgl/" fold

update the esp cmakelists in lvgl with "REQUIRES "esp_timer""
