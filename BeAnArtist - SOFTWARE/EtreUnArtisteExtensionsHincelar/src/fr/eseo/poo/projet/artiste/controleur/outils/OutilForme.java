package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.event.MouseEvent;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Forme;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;

public abstract class OutilForme extends Outil {
	
	public OutilForme() {
		super();
	}
	
	
	@Override
	public void mouseClicked(MouseEvent arg0) {
		super.mouseClicked(arg0);
		if(arg0.getClickCount()==2) {	
			VueForme form = creerVueForme();
			form.getForme().setPosition(getDebut());
			form.getForme().setHauteur(Forme.HAUTEUR_PAR_DEFAUT);
			form.getForme().setLargeur(Forme.LARGEUR_PAR_DEFAUT);
			this.getPanneauDessin().ajouterVueForme(form);
			System.out.println(form.getForme());
			this.getPanneauDessin().repaint();
		}
	}
	
	@Override
	public void mouseReleased(MouseEvent arg0) {
		super.mouseReleased(arg0);
		Coordonnees fin = new Coordonnees(arg0.getX(), arg0.getY());
		this.setFin(fin);
		VueForme form = creerVueForme();

		if(this.getDebut().getAbscisse() != this.getFin().getAbscisse() || 
				this.getDebut().getOrdonnee() != this.getFin().getOrdonnee() ) {
			this.getPanneauDessin().ajouterVueForme(form);
			this.getPanneauDessin().repaint();
		}
	}
	
	@Override
	public void mousePressed(MouseEvent arg0) {
		super.mousePressed(arg0);
		Coordonnees deb = new Coordonnees(arg0.getX(), arg0.getY());
		this.setDebut(deb);
	}
	
	protected abstract VueForme creerVueForme();

}
