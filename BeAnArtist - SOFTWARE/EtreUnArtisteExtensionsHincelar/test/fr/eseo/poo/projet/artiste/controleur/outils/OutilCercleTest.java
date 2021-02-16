package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauBarreOutils;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class OutilCercleTest {

	public static void main(String[] args) {
		new OutilCercleTest();
	}
	
	public OutilCercleTest() {
		outilCercleTest();
	}
	
	private void outilCercleTest() {
		
		JFrame fenetre = new JFrame();
		JPanel content = new JPanel();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		System.out.println(panneau.getVueFormes());
		PanneauBarreOutils barreOutils = new PanneauBarreOutils(panneau);

		fenetre.setTitle("VueCercleTest");
		fenetre.setSize(600, 400);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(false); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		OutilCercle outilCercle = new OutilCercle();
		outilCercle.setPanneauDessin(panneau);
		panneau.associerOutil(outilCercle);
		
		content.setLayout(new BorderLayout());	
		
		content.add(panneau, BorderLayout.WEST);
		content.add(barreOutils, BorderLayout.EAST);
		fenetre.setContentPane(content);

		fenetre.pack();
		fenetre.setVisible(true);		
		
	}

}
