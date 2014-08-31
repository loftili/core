function uninstall {
  rm -rf ./vendor
}

function install {
  mkdir -p ./vendor/rapidjson
  curl -o rapidjson.tar.gz http://ftp.sizethreestudios.com/artifacts/lofti.li/libs/rapidjson.tar.gz
  tar xvzf rapidjson.tar.gz -C ./vendor/rapidjson
}

uninstall
install
