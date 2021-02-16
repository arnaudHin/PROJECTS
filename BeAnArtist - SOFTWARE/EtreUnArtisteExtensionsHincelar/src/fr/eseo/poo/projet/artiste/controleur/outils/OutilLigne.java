package fr.eseo.poo.projet.artiste.controleur.outils;

import fr.eseo.poo.projet.artiste.modele.formes.Ligne;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;
import fr.eseo.poo.projet.artiste.vue.formes.VueLigne;

public class OutilLigne extends OutilForme {
	
	public OutilLigne() {
		super();
	}
	
	@Override
	protected VueForme creerVueForme() {
		Ligne ligne = new Ligne(this.getDebut());
		ligne.setC2(getFin());
		ligne.setCouleur(this.getPanneauDessin().getCouleurCourante());
		return new VueLigne(ligne);
	}
}











