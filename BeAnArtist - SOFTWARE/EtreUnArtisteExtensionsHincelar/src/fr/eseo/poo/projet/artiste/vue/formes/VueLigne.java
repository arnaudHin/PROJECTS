package fr.eseo.poo.projet.artiste.vue.formes;

import java.awt.Color;
import java.awt.Graphics2D;
import fr.eseo.poo.projet.artiste.modele.formes.Ligne;

public class VueLigne extends VueForme {	
	
	public VueLigne(Ligne ligne) {
		super(ligne);
	}
	
	@Override
	public void affiche(Graphics2D g2d) {
		Color coulCourante = g2d.getColor();
		g2d.setColor(this.getForme().getCouleur());		
		g2d.drawLine((int)this.getForme().getC1().getAbscisse() , 
				(int)this.getForme().getC1().getOrdonnee(),(int) this.getForme().getC2().getAbscisse(),
				(int) this.getForme().getC2().getOrdonnee());		
		g2d.setColor(coulCourante);		
	}
	
}














