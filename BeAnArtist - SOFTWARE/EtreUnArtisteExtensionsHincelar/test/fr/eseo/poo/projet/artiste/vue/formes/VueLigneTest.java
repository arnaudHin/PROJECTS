package fr.eseo.poo.projet.artiste.vue.formes;

import java.awt.Color;

import javax.swing.JFrame;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;

import fr.eseo.poo.projet.artiste.modele.formes.Ligne;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class VueLigneTest {

	public VueLigneTest() {
		testLigne();
	}
	
	public static void main(String[] args) {
		new VueLigneTest();
	}	
	
	private void testLigne() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);

		fenetre.setTitle("VueLigneTest");
		fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		Ligne ligne1 = new Ligne(10, 10);
		Ligne ligne2 = new Ligne(new Coordonnees(50, 50), 20, 20);
		ligne1.setCouleur(Color.red);
		VueLigne vl1 = new VueLigne(ligne1);
		VueLigne vl2 = new VueLigne(ligne2);
		
		panneau.ajouterVueForme(vl1);
		panneau.ajouterVueForme(vl2);


		fenetre.add(panneau);
		fenetre.pack();
		fenetre.setVisible(true);
		
	}

}




