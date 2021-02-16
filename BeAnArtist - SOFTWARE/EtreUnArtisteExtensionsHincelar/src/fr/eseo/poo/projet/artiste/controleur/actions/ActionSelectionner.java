package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import fr.eseo.poo.projet.artiste.controleur.outils.OutilSelectionner;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionSelectionner extends AbstractAction {
	
	public static final String NOM_ACTION = "ActionSelectionner"; 
	private PanneauDessin panneauDessin;

	public ActionSelectionner(PanneauDessin panneauDessin) { 
		super(ActionSelectionner.NOM_ACTION); 
		this.panneauDessin = panneauDessin; 
		}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		OutilSelectionner outilselect = new OutilSelectionner();
		outilselect.setPanneauDessin(this.panneauDessin);
		this.panneauDessin.associerOutil(outilselect);
	}
}
