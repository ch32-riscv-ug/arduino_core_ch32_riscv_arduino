<?php

chdir(dirname(__FILE__));
system('rm -rfv arduino_core_ch32_riscv_arduino*');
system('rm -rfv ArduinoCore-API-master');

$projects_name = 'arduino_core_ch32_riscv_arduino';
$base_ver = '1.1';
$ver = '1.1.0';

system("wget --continue https://github.com/ch32-riscv-ug/arduino_core_ch32_riscv_noneos/releases/download/$base_ver/arduino_core_ch32_riscv_noneos.$base_ver.zip");
system("unzip arduino_core_ch32_riscv_noneos.$base_ver.zip");
system('rm -rfv arduino_core_ch32_riscv_noneos/libraries/noneOS');
system("mv arduino_core_ch32_riscv_noneos $projects_name");

// update Arduono Core API
system("wget https://codeload.github.com/arduino/ArduinoCore-API/zip/refs/heads/master -O ArduinoCore-API-master.zip");
system("unzip ArduinoCore-API-master.zip");
system('rm -rfv copy/libraries/ArduinoCoreAPI/src/api');
system('cp -rfvp ArduinoCore-API-master/api copy/libraries/ArduinoCoreAPI/src/');

chdir($projects_name);

system('find . -name "*.patch" | xargs rm');

// copy copy
$cmd = "cp -rfvp ../copy/* .";
echo("exec $cmd\n");
system($cmd);

// getcwd()
$pwd = getcwd();

// patch
echo "################################################################\n";
echo "# patch\n";
$it = new RecursiveDirectoryIterator('.');
$it = new RecursiveIteratorIterator(
    $it,
    RecursiveIteratorIterator::LEAVES_ONLY
);
$patch_list = array();
foreach ($it as $file) {
    if(preg_match("/\.patch$/", $file->getFilename())) {
        $item = array();
        $item['path'] = $file->getPath();
        $item['file'] = $file->getFilename();
        $patch_list[] = $item;
    }
}

foreach($patch_list as $patch){
    chdir(dirname(__FILE__));
    chdir($projects_name);
    chdir($patch['path']);
    echo $patch['path'] . $patch['file'] . "\n";
    system("patch < " . $patch['file']);
}
echo "################################################################\n";

chdir(dirname(__FILE__));
system("zip -r $projects_name.$ver.zip $projects_name >zip.log");

// JSON
system("ls -la $projects_name.$ver.zip");
$ret = system("sha256sum $projects_name.$ver.zip");
$ret2 = explode(" ", $ret);
$hash = trim($ret2[0]);
echo "hash : '$hash'\n";

$filesize = filesize("$projects_name.$ver.zip");
echo "filesize : $filesize\n";

$jsonlist = glob("*.json");
foreach($jsonlist as $jsonfile){
  echo "json : $jsonfile\n";

  $file = file_get_contents($jsonfile);
  $data = json_decode($file, true);
  $data['packages'][0]['platforms'][0]['checksum'] = "SHA-256:$hash";
  $data['packages'][0]['platforms'][0]['size'] = $filesize;

  $json = json_encode($data, JSON_UNESCAPED_SLASHES | JSON_PRETTY_PRINT);
  file_put_contents($jsonfile, $json);
}
