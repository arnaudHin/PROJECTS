package fr.eseo.poo.projet.artiste.vue.formes;

import java.awt.Graphics2D;

import fr.eseo.poo.projet.artiste.modele.formes.Forme;

public abstract class VueForme {
	
	protected final Forme forme;	

	public VueForme(Forme forme) {
		this.forme = forme;
	}
	
	
	public Forme getForme() {
		return this.forme;
	}
	
	public abstract void affiche(Graphics2D g2d);

	
}












































