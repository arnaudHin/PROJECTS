package fr.eseo.poo.projet.artiste.vue.formes;

import java.awt.Color;


import java.awt.Graphics2D;
import java.util.List;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Etoile;

public class VueEtoile extends VueForme {
	private List<Coordonnees> sommets;
	private boolean remplie;

	public VueEtoile(Etoile etoile) {
		super(etoile);
		this.sommets = etoile.getCoordonnees();
		this.remplie = etoile.estRempli();
	}
	public void affiche(Graphics2D g2d) {
		Color coulCourante = g2d.getColor();		
		g2d.setColor(this.getForme().getCouleur());
		int[] pointsX = new int[this.sommets.size()];
		int[] pointsY = new int[this.sommets.size()];		
		for(int i = 0;i<this.sommets.size();i++) {
			pointsX[i] = (int) Math.round(this.sommets.get(i).getAbscisse());
			pointsY[i] = (int) Math.round(this.sommets.get(i).getOrdonnee());
		}	
		if(this.remplie) { 
			g2d.fillPolygon(pointsX, pointsY, this.sommets.size()); 
		}
		g2d.drawPolygon(pointsX, pointsY, this.sommets.size());	
		g2d.setColor(coulCourante);
	}


}
