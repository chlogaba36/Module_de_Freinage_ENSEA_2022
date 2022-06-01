Description de la partie IHM:

Ce que nous avons réalisé:
Commande d'un afficheur LCD Groove avec la carte STM32 Nucleo F410
Cette partie nous a pris beaucoup de temps (dû au manque de documentations, sont manque de qualité et à des librairies partielles en Arduino).
Ce que nous avons réussi à réaliser:
- Réaliser une connexion I2C
- Refaire une librairie entière pour l'écran LCD qui fonctionne et est documentée.
- Changer des menus (c'est-à-dire afficher plusieurs pattern d'écran).

Commande d'un bouton sur la carte STM32 Nucleo F410 (fonctionnement sensiblement identique à l'utilisation d'un bouton externe)

Commande d'un encodeur rotatif avec la carte STM32 Nucleo F410
Cette partie a été partiellement réalisé. Nous avons dans un premier temps pris en main le fonctionnement d'un encodeur, réalisé un premier code pour sa commande, il reste à réaliser la commande encodeur - microprocesseur - afficheur, qui n'est pas encore fonctionnelle.

Par manque de temps, nous avons effectué nos commandes sur la carte STM32 Nucleo F410. Pour passer au microprocesseur STM32G030K6T6, il faudrait changer les connexions (sur les pins et en physique), mais le code est sensiblement le même.
Pour effectuer nos commandes, nous avons utilisé abondamment les fonctions HAL.
