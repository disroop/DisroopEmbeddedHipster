#!/usr/bin/env bash
cd "$(dirname "$0")" || exit
function runWithDocker() {
  if [ "$(docker ps -q -f name=forty-jekyll-theme-1)" ]; then
    echo exists
    docker stop forty-jekyll-theme-1 || true && docker rm forty-jekyll-theme-1 || true
  else
    echo else
  fi
  open http://localhost:4002/DisroopEmbeddedHipster/
  docker run --rm --volume="$PWD:/srv/jekyll" -p 4002:4000 -it jekyll/jekyll:latest jekyll serve --watch --drafts
}

function run() {
  #oder
  open http://localhost:4000/DisroopEmbeddedHipster
  jekyll serve --watch --drafts --trace
}

#run
runWithDocker
