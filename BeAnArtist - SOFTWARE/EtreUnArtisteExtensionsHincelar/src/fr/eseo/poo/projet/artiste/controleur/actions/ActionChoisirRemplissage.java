package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionChoisirRemplissage extends AbstractAction {

	public static final String NOM_ACTION = "ActionChoisirRemplissage";
	private PanneauDessin panneauDessin;
	
	public ActionChoisirRemplissage(PanneauDessin panneauDessin) {
		super(ActionChoisirRemplissage.NOM_ACTION);
		this.panneauDessin = panneauDessin;	
		}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		this.panneauDessin.setModeRemplissage(! this.panneauDessin.getModeRemplissage());
	}

}
