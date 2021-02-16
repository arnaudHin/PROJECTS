package fr.eseo.poo.projet.artiste.vue.formes;

import java.awt.Graphics2D;
import java.awt.Color;
import fr.eseo.poo.projet.artiste.modele.formes.Ellipse;

public class VueEllipse extends VueForme {
	private boolean remplie;
	public VueEllipse(Ellipse ellipse) {
		super(ellipse);
		this.remplie = ellipse.estRempli();
	}
	@Override
	public void affiche(Graphics2D g2d) {
		Color coulCourante = g2d.getColor();
		g2d.setColor(this.getForme().getCouleur());
		if(this.remplie) {
			g2d.fillOval((int) this.getForme().getPosition().getAbscisse(),
					(int) this.getForme().getPosition().getOrdonnee(), 
					(int) this.getForme().getLargeur(),
				(int) this.getForme().getHauteur());
		}
		g2d.drawOval((int) this.getForme().getPosition().getAbscisse(), 
				(int) this.getForme().getPosition().getOrdonnee(), 
				(int) this.getForme().getLargeur(),
				(int) this.getForme().getHauteur());
		g2d.setColor(coulCourante);
		}

}








