FORMULA ONE
===========
## Credits  ######

Project by Andre Debuisne and Eric Charvillat
Created at EPITA during the formula one project, October 2018.
Contact : andre.debuisne@epita.fr | eric.charvillat@epita.fr.

---

The goal of the project is to write an AI that will control a formula one car,
making it go as fast as possible with as few commands as possible, without
crashing.

---

## Compilation ######

Requirements :

    * Unix-based Operating System (ArchLinux was used for this project),
    * GCC
    * Make

Using make, you can run these commands :

    * make run   --> launch the game UI
    * make check --> run tests to count the number of instructions used to
    reach the finish line
    * make ghost --> create a ghost, that can be used later while using make run
