package fr.eseo.poo.projet.artiste.controleur.outils;

import javax.swing.JFrame;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class OutilLigneTest {

	public static void main(String[] args) {
		new OutilLigneTest();
	}
	
	
	public OutilLigneTest() {
		outilLignetest();
	}
	
	private void outilLignetest() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin();

		fenetre.setTitle("VueLigneTest");
		fenetre.setSize(600, 400);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		OutilLigne outilLinge = new OutilLigne();
		
		outilLinge.setPanneauDessin(panneau);
		panneau.associerOutil(outilLinge);
		
		fenetre.add(panneau);
		fenetre.pack();
		fenetre.setVisible(true);
		
	}

}


