package fr.eseo.poo.projet.artiste.controleur.actions;

import java.awt.BorderLayout;
import java.awt.Color;

import javax.swing.JFrame;
import javax.swing.JPanel;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauBarreOutils;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class ActionChoisirRemplissageTest {

	public static void main(String[] args) {
		new ActionChoisirRemplissageTest();
	}
	
	public ActionChoisirRemplissageTest() {
		test();
	}
	
	private void test() {
		JFrame fenetre = new JFrame();
		JPanel content = new JPanel();
		PanneauDessin panneau = new PanneauDessin(600, 400, Color.white);
		PanneauBarreOutils barreOutils = new PanneauBarreOutils(panneau);

		fenetre.setTitle("VueLigneTest");
		fenetre.setSize(600, 400);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(false); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		content.setLayout(new BorderLayout());	
		
		content.add(panneau, BorderLayout.WEST);
		content.add(barreOutils, BorderLayout.EAST);
		fenetre.setContentPane(content);

		fenetre.pack();
		fenetre.setVisible(true);		
	}

}
