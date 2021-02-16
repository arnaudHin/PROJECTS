package fr.eseo.poo.projet.artiste.controleur.outils;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Ellipse;
import fr.eseo.poo.projet.artiste.vue.formes.VueEllipse;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;

public class OutilEllipse extends OutilForme {

	
	@Override
	protected VueForme creerVueForme() {
		double lar = (getFin().getAbscisse() - getDebut().getAbscisse());
		double hauteur = (getFin().getOrdonnee() - getDebut().getOrdonnee());		
		
		if(lar<0 && hauteur<0) {
			Coordonnees temp = getDebut();
			this.setDebut(getFin());
			this.setFin(temp);
		}
		if(lar<0 && hauteur>0) {
			this.setDebut(new Coordonnees(this.getDebut().getAbscisse()-Math.abs(lar), this.getDebut().getOrdonnee()));
			this.setFin(new Coordonnees(this.getFin().getAbscisse()+Math.abs(lar), this.getFin().getOrdonnee()));
		}
		if(lar>0 && hauteur<0) {
			this.setFin(new Coordonnees(this.getFin().getAbscisse(), this.getFin().getOrdonnee() + Math.abs(hauteur)));
			this.setDebut(new Coordonnees(this.getDebut().getAbscisse(), this.getDebut().getOrdonnee() - Math.abs(hauteur)));
		}
		
		Ellipse ellipse = new Ellipse(getDebut(), Math.abs(lar), Math.abs(hauteur));
		ellipse.setCouleur(this.getPanneauDessin().getCouleurCourante());
		ellipse.setRempli(this.getPanneauDessin().getModeRemplissage());
		
		return new VueEllipse(ellipse);

	}

}
