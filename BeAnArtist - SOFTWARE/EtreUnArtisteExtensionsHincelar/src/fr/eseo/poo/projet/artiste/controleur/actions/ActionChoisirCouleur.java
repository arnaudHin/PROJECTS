package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.Color;
import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JColorChooser;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionChoisirCouleur extends AbstractAction {

	public static final String NOM_ACTION = "ActionChoisirCouleur"; 
	private PanneauDessin panneauDessin;

	public ActionChoisirCouleur(PanneauDessin panneauDessin) { 
		super(ActionChoisirCouleur.NOM_ACTION); 
		this.panneauDessin = panneauDessin; 
		}
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		Color color = JColorChooser.showDialog(this.panneauDessin, ActionChoisirCouleur.NOM_ACTION, 
				this.panneauDessin.getCouleurCourante());
		this.panneauDessin.setCouleurCourante(color);
	}
}

