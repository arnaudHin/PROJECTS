package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.event.MouseEvent;


import javax.swing.event.MouseInputListener;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public abstract class Outil implements MouseInputListener {
	
	private Coordonnees debut;
	private Coordonnees fin;
	private PanneauDessin panneauDessin;
	
	public Coordonnees getDebut() { 
		return this.debut; 
		}
	public Coordonnees getFin() { 
		return this.fin; 
		}
	public void setDebut(Coordonnees debut) { 
		this.debut =  debut; 
		}
	public void setFin(Coordonnees fin) { 
		this.fin = fin; 
		}
	public PanneauDessin getPanneauDessin() { 
		return this.panneauDessin; 
		}
	public void setPanneauDessin(PanneauDessin pann) { 
		this.panneauDessin = pann; 
		} 

	@Override
	public void mouseClicked(MouseEvent arg0) {

	}

	@Override
	public void mouseEntered(MouseEvent arg0) {

	}

	@Override
	public void mouseExited(MouseEvent arg0) {

	}

	@Override
	public void mousePressed(MouseEvent arg0) {
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
	}

	@Override
	public void mouseDragged(MouseEvent arg0) {

	}

	@Override
	public void mouseMoved(MouseEvent arg0) {

	}

}
