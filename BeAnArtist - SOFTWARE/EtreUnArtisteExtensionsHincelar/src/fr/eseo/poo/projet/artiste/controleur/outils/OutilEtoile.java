package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.event.MouseEvent;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Etoile;
import fr.eseo.poo.projet.artiste.modele.formes.Forme;
import fr.eseo.poo.projet.artiste.vue.formes.VueEtoile;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauBarreOutils;

public class OutilEtoile extends OutilForme {
	
	private static Etoile etoile;
	private PanneauBarreOutils panneauBarreOutil;
	
	public OutilEtoile(PanneauBarreOutils panOutils) {
		this.panneauBarreOutil = panOutils;
	}
	

	protected VueForme creerVueForme() {
		double rayon = this.getDebut().distanceVers(this.getFin());
		double angle = this.getFin().angleVers(this.getDebut());
		Coordonnees center = this.getFin();		
		Coordonnees position = new Coordonnees();
		position = new Coordonnees(center.getAbscisse() - rayon, center.getOrdonnee() - rayon);
		int nombreBranches = (int) this.panneauBarreOutil.spinnerNombreBranche.getValue();
		double longueurBranche = (double) this.panneauBarreOutil.spinnerLongueurBranche.getValue();
		etoile = new Etoile(position, 2*rayon, nombreBranches, angle, longueurBranche);
		etoile.setCouleur(this.getPanneauDessin().getCouleurCourante());
		etoile.setRempli(this.getPanneauDessin().getModeRemplissage());
		return new VueEtoile(etoile);
	}
	
	public void mouseClicked(MouseEvent arg0) {		
		if(arg0.getClickCount()==2) {	
			this.etoile.setAnglePremiereBranche(Etoile.ANGLE_PREMIERE_BRANCHE_PAR_DEFAUT);
			this.etoile.setNombreBranches(Etoile.NOMBRE_BRANCHES_PAR_DEFAUT);
			this.etoile.setLongueurBranche(Etoile.LONGUEUR_BRANCHE_PAR_DEFAUT);
			this.etoile.setPosition(getDebut());
			this.etoile.setLargeur(Forme.LARGEUR_PAR_DEFAUT);
			this.etoile.setHauteur(Forme.LARGEUR_PAR_DEFAUT);
			this.getPanneauDessin().ajouterVueForme(new VueEtoile(etoile));
			this.getPanneauDessin().repaint();
		}
	}
}




