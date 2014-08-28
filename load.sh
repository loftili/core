function req {
  curl -o result.log --progress-bar --header 'x-loftili-auth: dadleyy' http://localhost:8888/stop
  curl -o result.log --progress-bar --header 'x-loftili-auth: dadleyy' http://localhost:8888/start
}

for (( c=1; c<=50; c++ ))
do
  req c
done
