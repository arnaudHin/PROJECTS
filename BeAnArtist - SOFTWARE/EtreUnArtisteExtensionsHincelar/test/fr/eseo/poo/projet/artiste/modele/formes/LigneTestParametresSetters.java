package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;

@RunWith(Parameterized.class)
public class LigneTestParametresSetters {
	private Coordonnees c1; 
	private Coordonnees c2; 
	private double largeur; 
	private double hauteur;
	
	public LigneTestParametresSetters(Coordonnees c1, Coordonnees c2, double largeur, double hauteur) {
		this.c1 = c1; 
		this.c2 = c2; 
		this.largeur = largeur; 
		this.hauteur = hauteur;
	}

	@Parameters(name= "dataLigne[{index}] : {0}, {1}, {2}, {3} ") 
	public static Collection<Object[]>dataLigne(){
		Object[][] dataLigne = new Object[][] {
			{new Coordonnees(10, 10), new Coordonnees(20, 20), 10, 10},
			{new Coordonnees(10, 10), new Coordonnees(5, 5), -5, -5},
			{new Coordonnees(10, 10), new Coordonnees(20, 5), 10, -5},
			{new Coordonnees(10, 10), new Coordonnees(5, 20), -5, 10},
			{new Coordonnees(0.1, 6.9), new Coordonnees(6.5, 4.3), 6.4, -(6.9-4.3)},
			{new Coordonnees(57.9, 96.3), new Coordonnees(1000, 1000), 1000-57.9, 1000-96.3}			
		};
		return Arrays.asList(dataLigne);}
	
	@Test
	public void testLargeurHauteurC2C1() {
		LigneTestParametresSetters testLHC2 = new LigneTestParametresSetters(c1, c2, largeur, hauteur);
		
		Ligne ligne = new Ligne(testLHC2.c1);
		ligne.setC2(testLHC2.c2);
		assertEquals("mauvaise hauteur", hauteur, ligne.getHauteur(), 0.1);
		assertEquals("mauvaise largeur", largeur, ligne.getLargeur(), 0.1);	
		
		Ligne ligne2 = new Ligne(testLHC2.c1);
		ligne2.setLargeur(testLHC2.largeur);
		ligne2.setHauteur(testLHC2.hauteur);
	
		assertEquals("mauvais X coordonnees de fin", c2.getAbscisse(), ligne2.getC2().getAbscisse(), 0.1 );
		assertEquals("mauvais Y coordonnees de fin", c2.getOrdonnee(), ligne2.getC2().getOrdonnee(), 0.1 );
		
		Ligne ligne3 = new Ligne(testLHC2.largeur, testLHC2.hauteur);
		ligne3.setPosition(testLHC2.c1);
		
		assertEquals("mauvais X coordonnees de fin", c2.getAbscisse(), ligne3.getC2().getAbscisse(), 0.1 );
		assertEquals("mauvais Y coordonnees de fin", c2.getOrdonnee(), ligne3.getC2().getOrdonnee(), 0.1 );		
		
	}
}
