# Poulp-o-player

Yeah, because I lack a better name

## Another music player? Why?

* I got bored of bulky music players
* I got bored of said music players doing everything BUT play music properly
* I needed a project to wrap up my C++ skills
* I felt like giving Qt a spin

## Ok, so what's the deal?

I plan many more features for this thing. As you can see its currently pretty minimal!
The whole idea is to keep is as small and minimal as possible, as I generally set a playlist up and then forget about it for a while.

## Wait wait wait. Lightweight? Qt?

I know it can sound rather incompatible, but yeah.
Ideally the footprint will not skyrocket as I go forward

Command line interface is NOT excluded
Changing the backend (currently a simple QMediaPlayer) is NOT excluded either

## Wait wait wait. Lightweight? Qt?

I know it can sound rather incompatible, but yeah.
Ideally the footprint will not skyrocket as I go forward

Command line interface is NOT excluded
Changing the backend (currently a simple QMediaPlayer) is NOT excluded either

## Sure. Why not do proper design up front then?

Cause it's final exam season and I just want to get my nose out the books for a bit

## Cool. So how do I start using it?

I currently don't generate builds for various platforms, so you are gonna have to build yourself.
I'm also trying to keep the build as simple as possible, so right now the build should look like:

```
qmake
make

./Poulp-o-player
```

Enjoy!

## So wait, what's the catch?

Let me put it simply for you... Ehhhh... It's dumb
It's using the system's audio framework, so if you dont have a system wide codec for your fancy format, it's not gonna work.


