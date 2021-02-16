package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.event.MouseEvent;

import javax.swing.JOptionPane;

import fr.eseo.poo.projet.artiste.controleur.actions.ActionSelectionner;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Forme;

public class OutilSelectionner extends Outil {
	
	private Forme formeSelectionnee;
	
	@Override
	public void mouseClicked(MouseEvent arg0) {
		super.mouseClicked(arg0);
		boolean selected = false;
		for (int i=0 ; i<this.getPanneauDessin().getVueFormes().size() ; i++) {
			if(this.getPanneauDessin().getVueFormes().get(i).getForme().contient(new Coordonnees(arg0.getX(), 
					arg0.getY()))) {
				this.formeSelectionnee = this.getPanneauDessin().getVueFormes().get(i).getForme();
				selected = true;
				continue;
			}
		}
		if(selected) {
			JOptionPane.showMessageDialog(this.getPanneauDessin(), formeSelectionnee.toString(), 
					ActionSelectionner.NOM_ACTION, JOptionPane.INFORMATION_MESSAGE);
		}
	}
}
