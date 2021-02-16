package fr.eseo.poo.projet.artiste.vue.formes;

import javax.swing.JFrame;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Cercle;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class VueCercleTest {

	
	public VueCercleTest() {
		testCercle();
	}
	
	private void testCercle() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);

		fenetre.setTitle("VueEllipseTest");
		fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false);
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		Cercle cercle1 = new Cercle(new Coordonnees(100, 100), 50);
		VueEllipse vcer1 = new VueEllipse(cercle1);
		
		Cercle cercle2 = new Cercle(new Coordonnees());
		VueEllipse vcer2 = new VueEllipse(cercle2);

		panneau.ajouterVueForme(vcer1);
		panneau.ajouterVueForme(vcer2);

		fenetre.add(panneau);
		fenetre.pack();
		fenetre.setVisible(true);
		
	}
	
		public static void main(String[] args) {
		new VueCercleTest();
	}
	
}
