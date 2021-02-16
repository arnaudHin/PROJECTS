package fr.eseo.poo.projet.artiste.controleur.outils;

import fr.eseo.poo.projet.artiste.modele.formes.Cercle;
import fr.eseo.poo.projet.artiste.vue.formes.VueCercle;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;
import java.awt.event.MouseEvent;


public class OutilCercle extends OutilForme {
	
	protected VueForme creerVueForme() {
		double deltaX = (getFin().getAbscisse() - getDebut().getAbscisse());
		double deltaY = (getFin().getOrdonnee() - getDebut().getOrdonnee());
		double cote = Math.max(Math.abs( deltaX ), Math.abs( deltaY ));
		
		if( deltaX <= 0 && deltaY <= 0) {
			if(cote == Math.abs( deltaY )) {
				getDebut().deplacerVers( this.getDebut().getAbscisse() - cote, this.getFin().getOrdonnee() ); }
			else {
				getDebut().deplacerVers( this.getFin().getAbscisse(), this.getDebut().getOrdonnee() - cote ); }	
		}
		else if(deltaX <= 0 && deltaY >= 0) {
			getDebut().deplacerVers( this.getDebut().getAbscisse()-cote, this.getDebut().getOrdonnee() ); }
		else if(deltaX >= 0 && deltaY <= 0) {
			getDebut().deplacerVers( this.getDebut().getAbscisse(), this.getDebut().getOrdonnee() - cote ); }
				
		Cercle cercle = new Cercle(getDebut(), cote);
		cercle.setCouleur(this.getPanneauDessin().getCouleurCourante());
		cercle.setRempli(this.getPanneauDessin().getModeRemplissage());
		return new VueCercle(cercle);
		
	}
	
	
	public void mouseClicked(MouseEvent arg0) {	
		super.mouseClicked(arg0);
	}
}
