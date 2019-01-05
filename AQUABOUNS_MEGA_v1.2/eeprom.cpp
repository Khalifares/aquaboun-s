
/* AQUABOUNS REEF, Automate pour la gestion d'aquarium recifal
   Copyright (C) 2018 par dj bouns

   Ce programme est un logiciel libre: vous pouvez le redistribuer
   et/ou le modifier selon les termes de la "GNU General Public
   License", tels que publiés par la "Free Software Foundation"; soit
   la version 2 de cette licence ou (à votre choix) toute version
   ultérieure.

   Ce programme est distribué dans l'espoir qu'il sera utile, mais
   SANS AUCUNE GARANTIE, ni explicite ni implicite; sans même les
   garanties de commercialisation ou d'adaptation dans un but spécifique.

   Se référer à la "GNU General Public License" pour plus de détails.
   Vous la trouverez dans l'onglet GNU_General_Public_License.h

   Vous devriez avoir reçu une copie de la "GNU General Public License"
   en même temps que ce programme; sinon, écrivez a la "Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA".*/


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Librairies $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include <EEPROM.h>

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fichiers $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
#include "eeprom.h"
#include "global.h"
#include "debug.h"
#include "affichage.h"

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Déclarations $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
paramS_t sauvegarde;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Fonctions $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
/* verifie si il y a des parametre dans l'eeprom, si non, chargement des parametre par default */
void etablirValeursParDefaut() {
  uint32_t lectureMotClef;
  EEPROM.get(adresseMotClef, lectureMotClef); // verifie si il y a des parametres dans l'eeprom
  if (lectureMotClef == motClef) { // il y a des parametres dans l'eeprom, on les charges
    EEPROM.get(adresseDeSauvegarde, sauvegarde);
    texteProgmemAuNextion(texte1, texteNextion2, vert); // champ, texte, couleur
  }
  else { // pas de parametre dans l'epprom, chargement des parametre pas default
    // page menu
    sauvegarde.tempeteAleatoireOn = false; // off tempete aleatoire
    sauvegarde.nourrissageON[numeroUn] = true; // on nourrissage 1
    sauvegarde.nourrissageON[numeroDeux] = true; // off nourrissage 2
    sauvegarde.remonteDelay = Actif; // on remonté
    sauvegarde.eclairageOnOffPwm[blanc1] = Pwm; // mode pwm
    sauvegarde.eclairageOnOffPwm[blanc2] = Pwm; // mode pwm
    sauvegarde.eclairageOnOffPwm[bleu1] = Pwm; // mode pwm
    sauvegarde.eclairageOnOffPwm[bleu2] = Pwm; // mode pwm
    sauvegarde.brassageOnOffPwm[numeroUn] = Pwm; // mode pwm
    sauvegarde.brassageOnOffPwm[numeroDeux] = Pwm; // mode pwm
    sauvegarde.brassageOnOffPwm[numeroTrois] = Pwm; // mode pwm
    // page config
    sauvegarde.puissanceMaxEclairage[blanc1] = 70 ; // puissance  en %
    sauvegarde.puissanceMaxEclairage[blanc2] = 70 ; // puissance  en %
    sauvegarde.puissanceMaxEclairage[bleu1] = 100 ; // puissance  en %
    sauvegarde.puissanceMaxEclairage[bleu2] = 100 ; // puissance  en %
    sauvegarde.leverSoleil = 43200ul; // heure debut lever Soleil en seconde
    sauvegarde.coucherSoleil = 79200ul; // heure fin couché Soleil en seconde
    sauvegarde.dureelevercoucher = 7200u; // temps de levé Soleil en seconde
    sauvegarde.alertetemperaturebasse = 25.5; // temperature de declanchement de la ventilation du bac
    sauvegarde.alertetemperaturehaute = 27.0; // temperature de declanchement de la ventilation du bac
    sauvegarde.ventilationaquarium = 26.7; // temperature de declanchement de la ventilation du bac
    sauvegarde.ventilationrampe = 35; //  temperature de declanchement de la ventilation de la rampe
    sauvegarde.adresseSondeRampe = 1; // adresse de la sonde de temperature de la rampe
    sauvegarde.adresseSondeBac = 0; // adresse de la sonde de temperature du bac
    sauvegarde.heureNourrissage[numeroUn] = 46800ul; // heure du nourrissage auto 1 en seconde
    sauvegarde.heureNourrissage[numeroDeux] = 72000ul; // heure du nourrissage auto 2 en seconde
    sauvegarde.dureeNourrissageMillis = 900000ul; // durée du Nourrissage en millis
    sauvegarde.dureeOsmolationMillis = 15000u; //durée de l'osmolation en millis
    sauvegarde.compteurOsmolationMax = 5; // nombre de declanchement de l'osmolation avant alarme
    sauvegarde.consignePhRac = 680; // consigne du ph du RAC sans decimal
    sauvegarde.alertephbacbas = 780; // limite PH bas du bac pour alerte sans decimal
    sauvegarde.alertephbachaut = 840;; // limite ph haut du bac pour alerte sans decimal
    // page brassage
    sauvegarde.puissanceMaxBrassage[numeroUn] = 60 ; // puissance jebao en %
    sauvegarde.puissanceMaxBrassage[numeroDeux] = 60 ; // puissance jebao en %
    sauvegarde.puissanceMaxBrassage[numeroTrois] = 60 ; // puissance jebao en %
    sauvegarde.angle1Oscillo[numeroUn] = 0 ; // angle oscillo entre 0 et 180
    sauvegarde.angle2Oscillo[numeroDeux] = 179 ; // angle oscillo entre 0 et 180
    sauvegarde.angle1Oscillo[numeroTrois] = 1 ; // angle oscillo entre 0 et 180
    sauvegarde.angle2Oscillo[numeroUn] = 178 ; // angle oscillo entre 0 et 180
    sauvegarde.angle1Oscillo[numeroDeux] = 2 ; // angle oscillo entre 0 et 180
    sauvegarde.angle2Oscillo[numeroTrois] = 177 ; // angle oscillo entre 0 et 180
    sauvegarde.delaisMouvementOscilloMillis[numeroUn] = 1000 ; // delais mouvement oscillo en millis
    sauvegarde.delaisMouvementOscilloMillis[numeroDeux] = 2000 ; // delais mouvement oscillo en millis
    sauvegarde.delaisMouvementOscilloMillis[numeroTrois] = 3000 ; // delais mouvement oscillo en millis
    sauvegarde.dureeTempeteMillis = 1800000ul; // durée tempête millis
    sauvegarde.puissanceTempete = 100; // puissance de toutes les pompe jebao en mode tempête en %
    sauvegarde.accalmieNocturne = 55; // pourcentage de reduction du brassage la nuit
    // page horloge
    sauvegarde.heureDebutAlerte = 36000; // heure debut alerte 10h en seconde
    sauvegarde.heureFinAlerte = 72000; // heure fin alerte 20h en seconde

    EEPROM.put(adresseDeSauvegarde, sauvegarde); // sauvegarde les parametre par default dans l'eeprom
    EEPROM.put(adresseMotClef, motClef); // ecrit le mots cle pour savoir que l'eeprom contient les données.
    texteProgmemAuNextion(texte1, texteNextion25, orange); // champ, texte, couleur
  }
  majValeursParDefaut(); // mettre a jour toute les variables ayant pour base un parametre chargé
}

/* met a jour toute les variables ayant pour base un parametre chargé
  a lancer apres chaque demarage ou sauvegarde */
void majValeursParDefaut() {
  const uint8_t nbrEtapes = 5; // pour avoir un chevauchement des couleurs dans la progression
  const uint16_t progression = (sauvegarde.dureelevercoucher / nbrEtapes); // duree du lever/coucher diviser par nbrEtapes pour avoir un chevauchement des couleurs dans la progression
  /* debut lever Soleil */
  debutleverSoleil[bleu1] = sauvegarde.leverSoleil;
  debutleverSoleil[bleu2] = (debutleverSoleil[bleu1] + progression);
  debutleverSoleil[blanc1] = (debutleverSoleil[bleu2] + progression);
  debutleverSoleil[blanc2] = (debutleverSoleil[blanc1] + progression);
  /* fin lever Soleil */
  finleverSoleil[blanc2] = (sauvegarde.leverSoleil + sauvegarde.dureelevercoucher);
  finleverSoleil[blanc1] = (finleverSoleil[blanc2] - progression);
  finleverSoleil[bleu2] = (finleverSoleil[blanc1] - progression);
  finleverSoleil[bleu1] = (finleverSoleil[bleu2] - progression);
  /* debut coucher Soleil */
  debutcoucherSoleil[blanc1] = (sauvegarde.coucherSoleil - sauvegarde.dureelevercoucher);
  debutcoucherSoleil[blanc2] = (debutcoucherSoleil[blanc1] + progression);
  debutcoucherSoleil[bleu1] = (debutcoucherSoleil[blanc2] + progression);
  debutcoucherSoleil[bleu2] = (debutcoucherSoleil[bleu1] + progression);
  /* fin coucher Soleil */
  fincoucherSoleil[bleu2] = sauvegarde.coucherSoleil;
  fincoucherSoleil[bleu1] = (fincoucherSoleil[bleu2] - progression);
  fincoucherSoleil[blanc2] = (fincoucherSoleil[bleu1] - progression);
  fincoucherSoleil[blanc1] = (fincoucherSoleil[blanc2] - progression);
  /* puissance brassage */
  puissanceMinBrassage[numeroUn] = sauvegarde.puissanceMaxBrassage[numeroUn] - ((sauvegarde.puissanceMaxBrassage[numeroUn] * sauvegarde.accalmieNocturne) / cent);
  puissanceMinBrassage[numeroDeux] = sauvegarde.puissanceMaxBrassage[numeroDeux] - ((sauvegarde.puissanceMaxBrassage[numeroDeux] * sauvegarde.accalmieNocturne) / cent);
  puissanceMinBrassage[numeroTrois] = sauvegarde.puissanceMaxBrassage[numeroTrois] - ((sauvegarde.puissanceMaxBrassage[numeroTrois] * sauvegarde.accalmieNocturne) / cent);
}
