package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.awt.Color;
import java.util.Locale;

import javax.swing.UIManager;

import org.junit.Test;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;

public class EtoileTestBasesCouleur {
	
	@Test
	public void testConstructeur1() {
		Etoile etoile1 = new Etoile(new Coordonnees(), 2, 3, 0, 1);
		Etoile etoile2 = new Etoile(new Coordonnees(10, 10), 5);
		Etoile etoile3 = new Etoile(10);
		Etoile etoile4 = new Etoile(new Coordonnees(6, 6));
		Etoile etoile5 = new Etoile();
		
		assertEquals("cons 1 position x", 0.0, etoile1.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 1 angle", 0.0, etoile1.getAnglePremiereBranche(), 0.1);
		assertEquals("cons 1 sommets", 2*etoile1.getNombreBranches(), etoile1.getCoordonnees().size(), 0.1);
		assertEquals("cons 1 longueurBranches", 1, etoile1.getLongueurBranche(), 0.1);
		assertEquals("cons 1 largeur", 2, etoile1.getLargeur(), 0.1);

		assertEquals("cons 2 position x", 10, etoile2.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 2 sommets", 2*etoile2.getNombreBranches(), etoile2.getCoordonnees().size(), 0.1);
		assertEquals("cons 2 largeur", 5, etoile2.getLargeur(), 0.1);

		assertEquals("cons 3 position x", 0, etoile3.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 3 sommets", 2*etoile3.getNombreBranches(), etoile3.getCoordonnees().size(), 0.1);
		assertEquals("cons 3 largeur", 10, etoile3.getLargeur(), 0.1);	
		
		assertEquals("cons 4 position x", 6, etoile4.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 4 sommets", 2*etoile4.getNombreBranches(), etoile4.getCoordonnees().size(), 0.1);
		assertEquals("cons 4 largeur", etoile4.getHauteur(), etoile4.getLargeur(), 0.1);	

		
		assertEquals("cons 5 position x", 0, etoile5.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 5 sommets", 2*etoile5.getNombreBranches(), etoile5.getCoordonnees().size(), 0.1);
		assertEquals("cons 5 largeur", etoile5.getHauteur(), etoile5.getLargeur(), 0.1);	
	}
	
	@Test
	public void testDeplacer() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		etoile.deplacerDe(1, 1);
		assertEquals("deplacer de : position X", 1 , etoile.getPosition().getAbscisse(), 0.1);		
		assertEquals("deplacer de : position Y", 1 , etoile.getPosition().getOrdonnee(), 0.1);
		assertEquals("deplacer de : cadreMax X", 3 , etoile.getCadreMaxX(), 0.1);		
		assertEquals("deplacer de : cadreMax Y", 3 , etoile.getCadreMaxY(), 0.1);		
	}
	@Test
	public void testAire() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		assertEquals("Aire", 2*etoile.getNombreBranches() , etoile.perimetre(), 0.1);		
	}
	@Test
	public void testPerimetre() {
	
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		assertEquals("perimetre 1", 2*etoile.getNombreBranches()*
				etoile.getCoordonnees().get(0).distanceVers(etoile.getCoordonnees().get(1)), 
				etoile.perimetre(), 0.1);	
		assertEquals("perimetre 2", 2*etoile.getNombreBranches() , etoile.perimetre(), 0.1);	
	}
	@Test
	public void testToString() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		assertEquals("to string non rempli", "[Etoile] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre :"
				+ " 6,0 aire : 2,6 couleur = R51,V51,B51" , etoile.toString());	
		etoile.setRempli(true);
		assertEquals("to string rempli", "[Etoile-Rempli] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre : "
				+ "6,0 aire : 2,6 couleur = R51,V51,B51" , 
				etoile.toString());	
		
		etoile.setRempli(false);
		
		Locale.setDefault(new Locale("en"));
		assertEquals("to string non rempli en", "[Etoile] : pos (0.0 , 0.0) dim 2.0 x 2.0 périmètre : "
				+ "6.0 aire : 2.6 couleur = R51,G51,B51" , 
				etoile.toString());	
		
		etoile.setRempli(true);
		
		assertEquals("to string rempli en", "[Etoile-Rempli] : pos (0.0 , 0.0) dim 2.0 x 2.0 périmètre : "
				+ "6.0 aire : 2.6 couleur = R51,G51,B51" , 
				etoile.toString());	
		
	
		Locale.setDefault( new Locale("fr"));
		
	}
	@Test
	public void testCouleur() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		assertEquals("couleur par defaut", UIManager.getColor("Panel.foreground") , etoile.getCouleur());	
		etoile.setCouleur(Color.ORANGE);
		assertEquals("set couleur orange", Color.ORANGE , etoile.getCouleur());	
	}
	@Test
	public void testRemplie() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0);
		assertEquals("non remplie", false , etoile.estRempli());	
		etoile.setRempli(true);
		assertEquals("remplie", true , etoile.estRempli());		
	}
	@Test
	public void testSpecialSetter() {
		Etoile etoile = new Etoile(new Coordonnees(), 2, 3, 0, 0.8);
		etoile.setLargeur(15);
		etoile.setLongueurBranche(0);
		etoile.setLargeur(30);
		etoile.setHauteur(20);
		
		
		
	}

}
