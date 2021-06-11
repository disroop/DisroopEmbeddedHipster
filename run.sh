#!/usr/bin/env bash
cd "$(dirname "$0")" || exit
 function runWithDocker() {
     if [ "$(docker ps -q -f name=forty-jekyll-theme-1)" ]; then
       echo exists
       docker stop forty-jekyll-theme-1 || true && docker rm forty-jekyll-theme-1 || true
     else
       echo else
     fi
     open http://localhost:4001/DisroopEmbeddedHipster
     docker run --rm --name forty-jekyll-theme-1 --volume="$(pwd):/srv/jekyll" -p 4001:4000 -it  jekyll/jekyll:latest  jekyll serve --watch --drafts
 }

function run() {
    #oder
  open http://localhost:4000
  jekyll serve --watch --drafts --trace
}


#run
runWithDocker