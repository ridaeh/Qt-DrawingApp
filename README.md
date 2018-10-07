# Qt-DrawingApp
Editeur graphique genre Paint réalisé en C++ avec Qt

# Screenshots
<p align="center">
<img src="https://github.com/ridaeh/Qt-DrawingApp/blob/master/rdme/app.png" width="602" height="630"/>
</p>

## Commencer

Ces instructions vous obtiendrez une copie du projet opérationnel sur votre ordinateur local à des fins de développement et de test. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

De quoi avez-vous besoin pour installer le logiciel et comment les installer?

Sous Ubuntu :
```
sudo apt-get install qt4-qmake

sudo apt-get install libqt4-dev

```

### Installation

Telechargez une copie du projet et ajouter la permission de l'execution au prog.

```
chmod +x Qt-DrawingApp

```

Maintenant le prog est prête à s'excuter.

```
./Qt-DrawingApp

```


## Développement et test

Faire dabord un Clean si vous avez un makefile:

```
make clean
```
si no,vous pouvez la générer :

```
qmake-qt4 -project
```
vous allez obtenir un fichier genre nomDeDossie.pro (.pro) et aprés:

```
qmake-qt4 -ceFichierGenerer.pro
```
et Voila vous avez maintenant un makefile.

Pour commpiler et executer le prog :
```
make
./Qt-DrawingApp
```
