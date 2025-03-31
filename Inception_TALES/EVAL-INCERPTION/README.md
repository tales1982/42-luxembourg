# Projet Inception - Validation des configurations Docker avec `make eval`

<div align="center">
  <img src="https://img.shields.io/badge/container-Docker-blue" alt="Docker">
  <img src="https://img.shields.io/badge/docker%20compose-v2.28.1-blue" alt="Docker Compose">
  <img src="https://img.shields.io/badge/makefile-eval-orange" alt="Makefile Eval">
  <img src="https://img.shields.io/badge/database-MariaDB-blue" alt="MariaDB">
  <img src="https://img.shields.io/badge/web%20server-Nginx-green" alt="Nginx">
  <img src="https://img.shields.io/badge/cms-WordPress-blueviolet" alt="WordPress">
  <img src="https://img.shields.io/badge/ssl-TLSv1.2%2Fv1.3-brightgreen" alt="SSL TLS">
  <img src="https://img.shields.io/badge/school-42-green" alt="42">
  <img src="https://img.shields.io/badge/42-Paris-blue" alt="42 Paris">
</div>

## Aperçu du projet

Ce dépôt contient uniquement un **Makefile** destiné à être utilisé par les étudiants de l'école 42 pour valider les configurations Docker dans le cadre de projets comme *Inception*. La commande principale, `make eval`, permet de s'assurer que les bonnes pratiques Docker sont respectées en vérifiant les fichiers de configuration, les variables d'environnement et les paramètres de sécurité.


## Description

La commande `make eval` est un outil puissant qui automatise la validation de votre environnement Docker. Elle vérifie que :
- Les fichiers requis sont présents (par exemple, `.env`, Dockerfiles).
- Les Dockerfiles respectent la structure correcte.
- Les certificats SSL et les ports sont correctement configurés (HTTPS uniquement sur le port 443).
- Aucune configuration interdite comme `network: host`, `--link` ou les boucles infinies (`tail -f`, `sleep infinity`) n'est présente.

En exécutant `make eval`, vous garantissez que votre environnement Docker respecte toutes les exigences nécessaires pour le projet *Inception*.

## Prérequis

Avant de lancer le projet, assurez-vous que votre environnement respecte les prérequis suivants :

- **Docker** : Version `27.0.3` ou ultérieure.
- **Docker Compose** : Version `v2.28.1` ou ultérieure.
- **GNU Make** : Version `4.3` ou ultérieure.
- Système d'exploitation : **Linux** (Ubuntu/Debian recommandé).
- **OpenSSL** : 3.0.2
- **ss** (iproute2) : iproute2-5.15.0
- **xdg-open** : 1.1.3
- **curl** : 7.81.0
- **grep** : 3.7

## Installation et Configuration

### Étape 1 : Cloner le dépôt


Clonez ce dépôt pour récupérer le **Makefile** :
```bash
git clone git@github.com:raveriss/docker-eval-suite.git
```

### Étape 2 : Copier le Makefile dans votre projet
Placez le fichier Makefile à la racine de votre projet Inception ou tout autre projet Docker que vous souhaitez valider.

```bash
made-f0Ar7s1% ls /chemin/vers/votre/projet/
Makefile  srcs
```

### Étape 3 : Lancer la commande make eval
Une fois le Makefile placé dans la racine de votre projet, exécutez la commande suivante pour lancer la validation :

```bash
make eval
```

### Étape 4 : Configurer le fichier .env
Le fichier `.env` contient les variables d'environnement nécessaires à votre configuration Docker. Remplissez-le correctement en ajoutant les variables suivantes :

```env
# Nom de domaine pour le site WordPress
DOMAIN_NAME=student.42.fr

# Nom de la base de données SQL
SQL_DATABASE=sql_database

# Nom d'utilisateur pour la base de données SQL
SQL_USER=sql_user

# Mot de passe pour l'utilisateur de la base de données SQL
SQL_PASSWORD=sql_password

# Mot de passe root pour la base de données SQL
SQL_ROOT_PASSWORD=sql_root_password

# Titre du site WordPress
SITE_TITLE="Official_Site"

# Nom d'utilisateur pour l'administrateur WordPress
ADMIN_USER=firstuser

# Mot de passe pour l'administrateur WordPress
ADMIN_PASSWORD=firstuserpassword

# Adresse e-mail de l'administrateur WordPress
ADMIN_EMAIL=firstuser@exemple.com

# Nom d'un second utilisateur WordPress
SECOND_USER=seconduser

# Mot de passe pour le second utilisateur WordPress
SECOND_PASSWORD=seconduserpassword

# Confirmation du mot de passe pour le second utilisateur WordPress
SECOND_USER_PASSWORD=seconduserpassword

# Adresse e-mail du second utilisateur WordPress
SECOND_USER_EMAIL=seconduser@exemple.com
```
Assurez-vous de ne pas exposer d'informations sensibles dans votre fichier .env.

### Étape 5 : Valider la configuration

**Validation du fichier** `.env` :
S'assure que toutes les variables requises sont présentes.
Vérifie qu'aucune information d'identification critique n'est exposée dans le fichier `.env`.

**Validation des Dockerfiles** :
Vérifie que chaque service (ex : NGINX, WordPress, MariaDB) possède un Dockerfile correspondant.
S'assure que les Dockerfiles ne contiennent pas de configurations interdites comme des boucles infinies.

**Validation du fichier docker-compose.yml** :
Vérifie qu'aucune option interdite telle que network: host ou --link n'est utilisée.
S'assure qu'un réseau Docker personnalisé est configuré.

**Validation SSL/TLS et des ports** :
Confirme que NGINX fonctionne uniquement sur le port 443 avec un certificat SSL/TLS valide.
S'assure que HTTP (port 80) est désactivé et redirigé vers HTTPS.


### Exemple de sortie
Après avoir exécuté make eval, vous devriez obtenir une sortie similaire à ceci :

```plaintext
[OK] Aucun identifiant critique trouvé dans .env.
[OK] Tous les Dockerfiles requis sont présents et valides.
[OK] docker-compose.yml ne contient pas de configurations interdites.
[OK] Le certificat SSL/TLS est valide et NGINX fonctionne sur le port 443.
[OK] Le site WordPress est correctement configuré sans exposition via HTTP.
```
En cas de problème, vous verrez des messages d'erreur détaillant les configurations manquantes ou incorrectes :

```plaintext
[Erreur] Le fichier `.env` est manquant ou incomplet.
[Erreur] NGINX est accessible via des ports autres que 443.
[Erreur] Aucun réseau Docker nommé 'inception' n'a été trouvé.
```
### Erreurs fréquentes et solutions
Voici quelques problèmes courants que vous pourriez rencontrer lors de l'exécution de make eval :

1. Fichier `.env` manquant
Message d'erreur :

```plaintext
[Erreur] `.env` est manquant dans srcs.
```
Solution : Assurez-vous de créer un fichier `.env` dans le répertoire srcs avec toutes les variables requises.


2. Dockerfile invalide
Message d'erreur :

```plaintext
[Erreur] Le Dockerfile pour nginx est manquant ou vide.
```
Solution : Vérifiez que chaque répertoire de service (ex : nginx, wordpress, mariadb) contient un Dockerfile valide et complet.


3. SSL/TLS non configuré
Message d'erreur :

```plaintext
[Erreur] Aucun certificat SSL/TLS détecté.
```
Solution : Assurez-vous que votre service NGINX est configuré avec un certificat SSL/TLS et fonctionne sur le port 443.


4. Configurations interdites dans docker-compose.yml
Message d'erreur :

```plaintext
[Erreur] docker-compose.yml contient 'network: host' ou '--link'.
```
Solution : Supprimez les configurations interdites dans votre fichier docker-compose.yml et assurez-vous d'utiliser un réseau Docker personnalisé.

### Contribution
Si vous souhaitez contribuer au projet, vous pouvez modifier le Makefile pour ajouter de nouveaux tests ou configurations. Par exemple, vous pouvez ajouter des vérifications pour de nouveaux services ou implémenter des validations de sécurité supplémentaires.

Pour modifier les tests, ouvrez le Makefile et éditez la cible eval. Les contributions sont les bienvenues, en particulier de la part des étudiants de l'école 42 !
