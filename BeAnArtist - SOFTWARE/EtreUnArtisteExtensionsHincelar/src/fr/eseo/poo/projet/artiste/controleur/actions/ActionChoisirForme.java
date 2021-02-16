package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.event.ActionEvent;


import javax.swing.AbstractAction;

import fr.eseo.poo.projet.artiste.controleur.outils.OutilCercle;
import fr.eseo.poo.projet.artiste.controleur.outils.OutilEllipse;
import fr.eseo.poo.projet.artiste.controleur.outils.OutilEtoile;
import fr.eseo.poo.projet.artiste.controleur.outils.OutilLigne;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauBarreOutils;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionChoisirForme extends AbstractAction {
	public static final String NOM_ACTION_LIGNE = "Ligne";
	public static final String NOM_ACTION_ELLIPSE = "Ellipse";
	public static final String NOM_ACTION_CERCLE = "Cercle";
	public static final String NOM_ACTION_ETOILE = "Etoile";

	private PanneauDessin panneauDessin; 
	private PanneauBarreOutils panBarreOutil; 
	private String action;

	public ActionChoisirForme(PanneauDessin panneauDessin, PanneauBarreOutils panBarreOutil, String  nameAction) {
		super(nameAction);
		this.panneauDessin = panneauDessin;
		this.panBarreOutil = panBarreOutil;
		this.action = nameAction;
	}

	public void actionPerformed(ActionEvent arg0) {
		if(this.action == ActionChoisirForme.NOM_ACTION_LIGNE) {
			OutilLigne outilLigne = new OutilLigne();
			outilLigne.setPanneauDessin(this.panneauDessin);
			this.panneauDessin.associerOutil(outilLigne);
		}
		else if(this.action == ActionChoisirForme.NOM_ACTION_ELLIPSE) {
			OutilEllipse outilEllipse = new OutilEllipse();
			outilEllipse.setPanneauDessin(this.panneauDessin);
			this.panneauDessin.associerOutil(outilEllipse);		}
		
		else if(this.action == ActionChoisirForme.NOM_ACTION_CERCLE) {
			OutilCercle outilCercle = new OutilCercle();
			outilCercle.setPanneauDessin(this.panneauDessin);
			this.panneauDessin.associerOutil(outilCercle);		}
		else if(this.action == ActionChoisirForme.NOM_ACTION_ETOILE) {
			OutilEtoile outiletoile = new OutilEtoile(this.panBarreOutil);
			outiletoile.setPanneauDessin(this.panneauDessin);
			this.panneauDessin.associerOutil(outiletoile);
		}
	}
}

